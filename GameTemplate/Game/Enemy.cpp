#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EXP.h"
#include "Attack.h"
#include "Game.h"
#include "EnemySpawn.h"
//�������g����悤�ɂ���
#include <random>
//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

namespace
{
	//�����𐶐�
	constexpr int MIN = -800;//�����͈͍̔Œ�l
	constexpr int MAX = 800;//�����͈͍̔ő�l
	constexpr int RAND_NUMS_TO_GENERATE = 2;//�����𐶐������
	//const int E_MUSH_MAXHP = 10;//�L�m�R�̍ő�HP
	const int MUSHMOVESPEED = 1.95f;//�L�m�R�̈ړ����x
}

bool Enemy::Start()
{
	m_player = FindGO<Player>("player");
	//�G�̗����B
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	int enepos = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (enepos) {
		case 0:
			m_position.x = m_player->GetPlayerPosition().x + distr(eng);
			enepos++;
			break;
		case 1:
			m_position.z = m_player->GetPlayerPosition().z + distr(eng);
			break;
		}
	}

	if (0.0f < m_player->GetPlayerPosition().x + m_position.x)
	{
		m_position.x += 100.0f;
	}
	else if (m_player->GetPlayerPosition().x + m_position.x <= 0.0f)
	{
		m_position.x -= 100.0f;
	}

	if (0.0f < m_player->GetPlayerPosition().z + m_position.z)
	{
		m_position.z += 100.0f;
	}
	else if (m_player->GetPlayerPosition().z + m_position.z <= 0.0f)
	{
		m_position.z -= 100.0f;
	}

	//���f���̓ǂݍ���
	m_enemy.Init("Assets/modelData/model/mush/bluemush.tkm", false);

	//�������B
	m_enemy.SetScale(0.3f, 0.3f, 0.3f);
	m_enemy.SetRotation(m_rotation);
	m_enemy.SetPosition(m_position);
	m_enemy.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//Box��̃R���W�������쐬����B
	m_collisionObject->CreateBox(m_position,       //���W�B
		Quaternion::Identity,                                   //��]�B
		{ 40.0f,40.0f,40.0f });                                                //Box�̑傫���B
	//���O��t����B
	m_collisionObject->SetName("enemy_hit");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);

	//EnemyHP();

	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 3)
	{
		m_hp = 20;
	}
	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 2)
	{
		m_hp = 10;
	}
	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 1)
	{
		m_hp = 1;
	}

	return true;
}
void Enemy::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		if (m_hp <= 0)
		{
			m_exp = NewGO<EXP>(0, "exp");
			m_exp->SetEXPPos(m_position);
			//m_plmanagement->AddEXP();
			DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
		//���E���~�܂��Ă��Ȃ��Ȃ�
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			m_attack = FindGO<Attack>("attack");
			Move();
			Rotation();
			//���f���̍X�V�����B
			m_enemy.Update();
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(m_collisionObject);
		DeleteGO(this);
	}
}

void Enemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_enemy.SetRotation(m_rotation);

	//�v���C���[�̑O�x�N�g�����v�Z����B
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Enemy::Move()
{
	m_playerposition = m_player->GetPlayerPosition();
	//�G�l�~�[���ړ�������B
	Vector3 diff = m_playerposition - m_position;
	diff.Normalize();
	//���x�������
	m_moveSpeed = diff * MUSHMOVESPEED;
	m_position += m_moveSpeed;

	//���W��ݒ肷��B
	m_enemy.SetPosition(m_position);

	//�q�b�g����p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("BulletAttack");

	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//�e�̃R���W�����ƓG�̃R���W�������B
		//�Փ˂��Ă�����B
		if (collision->IsHit(m_collisionObject) == true)
		{
			m_hp--;
		}
	}

	Vector3 m_collisionPosition = m_position;
	m_collisionPosition.y = 20.0f;
	//setposition�œ������G�̓����蔻��̔��f
	m_collisionObject->SetPosition(m_collisionPosition);
}
void Enemy::EnemyHP()
{
	m_mushhpbar.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);
	m_mushhpbar.SetPosition(Vector3(-660.0f, -363.0f, 0.0f));
}
void Enemy::Render(RenderContext& rc)
{
	//m_mushhpbar.Draw(rc);
	m_enemy.Draw(rc);
}