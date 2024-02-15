#include "stdafx.h"
#include "Attack.h"
#include "Player.h"
#include "Game.h"

//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"
//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "graphics/effect/EffectEmitter.h"
//�������g����悤�ɂ���
#include <random>

namespace
{
	//�����𐶐�
	constexpr int MIN = -600;//�����͈͍̔Œ�l
	constexpr int MAX = 600;//�����͈͍̔ő�l
	constexpr int RAND_NUMS_TO_GENERATE = 2;//�����𐶐������
}

bool Attack::Start()
{
	//�e
	if (m_attackno == 0)
	{
		m_player = FindGO<Player>("player");
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = m_player->GetPlayerPosition();
			//if (m_attackA == 0)
			//{
			//	m_position += m_side*20.0f;
			//}
			//if (m_attackA == 1)
			//{
			//	m_position -= m_side * 20.0f;
			//}
		m_position.y += 40.0f;
		m_position += m_moveSpeed * 10.0f;
		m_playerposition = m_player->GetPlayerPosition();
		//�e�̃��f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm",true,true);
		m_modelRender.SetScale({ 0.2f,0.2f,0.2f });
		//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		//�R���C�_�[������������B
		m_sphereCollider.Create(48.0f);

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//���W��G�̈ʒu�ɐݒ肷��B
		collisionPosition = m_position;
		//Box��̃R���W�������쐬����B
		m_collisionObject->CreateBox(collisionPosition,       //���W�B
			m_player->GetPlayerRot(),                                 //��]�B
			{ 40.0f,20.0f,20.0f });                                                //Box�̑傫���B
			//���O��t����B
		m_collisionObject->SetName("BulletAttack");
		//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
		m_collisionObject->SetIsEnableAutoDelete(false);
	}
	//����
	else if (m_attackno == 1)
	{
		m_player = FindGO<Player>("player");
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = m_player->GetPlayerPosition();
		m_position.y = 500.0f;
		//�G�̗����B
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_int_distribution<int> distr(MIN, MAX);
		int holypos = 0;
		for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
			switch (holypos) {
			case 0:
				m_position.x = m_position.x + distr(eng);
				holypos++;
				break;
			case 1:
				m_position.z = m_position.z + distr(eng);
				break;
			}
		}
		//���f���̓ǂݍ���
		m_modelRender.Init("Assets/modelData/holywater.tkm", true, false);
		//m_rotation.AddRotationDegY(180.0f);
		m_modelRender.SetScale({ 3.0f,3.0f,3.0f });
		//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		//�R���C�_�[���������B
		m_sphereCollider.Create(48.0f);

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//���W��G�̈ʒu�ɐݒ肷��B
		collisionPosition = m_position;
		//����̃R���W�������쐬����B
		m_collisionObject->CreateBox(collisionPosition,       //���W�B
			Quaternion::Identity,                                   //��]�B
			{ 100.0f,8.0f,100.0f});                                                //���̑傫��(���a)�B
			//"BulletAttack"�͉����A�����B
		m_collisionObject->SetName("BulletAttack");
		//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
		m_collisionObject->SetIsEnableAutoDelete(false);
		return true;

	}
	//�n��
	else if (m_attackno == 2)
	{
		m_player = FindGO<Player>("player");
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = m_player->GetPlayerPosition();
		m_position.y = 5.0f;
		m_position -= m_moveSpeed * 30.0f;
		//���f���̓ǂݍ���
		m_modelRender.Init("Assets/modelData/mine.tkm", true, false);
		m_rotation.SetRotationDegY(50.0f);
		m_modelRender.SetScale({ 2.0f,2.0f,2.0f });
		//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.Update();
		//�R���C�_�[���������B
		m_sphereCollider.Create(48.0f);

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//���W��G�̈ʒu�ɐݒ肷��B
		collisionPosition = m_position;
		//����̃R���W�������쐬����B
		m_collisionObject->CreateBox(collisionPosition,       //���W�B
			Quaternion::Identity,                                   //��]�B
			{ 100.0f,8.0f,100.0f });                                                //���̑傫��(���a)�B
			//"BulletAttack"�͉����A�n���B
		m_collisionObject->SetName("BulletAttack");
		//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
		m_collisionObject->SetIsEnableAutoDelete(false);
		return true;

	}
	//�u�[������
	else if (m_attackno == 3)
	{
		m_player = FindGO<Player>("player");
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = m_player->GetPlayerPosition();
		m_position.y += 40.0f;
		m_position += m_moveSpeed * 10.0f;
		m_playerposition = m_player->GetPlayerPosition();
		//�e�̃��f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/boomerang.tkm", false, false);
		m_modelRender.SetScale({ 2.0f,1.0f,2.0f });
		//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		//�R���C�_�[���������B
		m_sphereCollider.Create(48.0f);

		//�R���W�����I�u�W�F�N�g���쐬����B
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//���W��G�̈ʒu�ɐݒ肷��B
		collisionPosition = m_position;
		//Box��̃R���W�������쐬����B
		m_collisionObject->CreateBox(collisionPosition,       //���W�B
			m_player->GetPlayerRot(),                                   //��]�B
			{ 60.0f,30.0f,30.0f });                                                //Box�̑傫���B
			//���O��t����B
		m_collisionObject->SetName("BulletAttack");
		//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
		m_collisionObject->SetIsEnableAutoDelete(false);
	}
	return true;
}

Attack::Attack()
{

}

Attack::~Attack()
{
	DeleteGO(m_collisionObject);
}

void Attack::Update() //���1�b�Ԃ�60��Ăяo�����
{
	if (FindGO<Game>("game") != NULL)
	{
		//���E���~�܂��Ă��Ȃ��Ȃ�
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			//���U���ŁA�^�C�}�[��4.9�b�ȓ��Ȃ�
			if (m_attackno == 3 && m_deletetimer <= 4.9f)
			{
				//�q�b�g����p�̃R���W�����̔z����擾�B
				const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_hit");

				//for���Ŕz����񂷁B
				for (auto collision : collisions)
				{
					//�e�̃R���W�����ƓG�̃R���W�������B
					//�Փ˂��Ă��āA�o�E���h�񐔂�4��ȉ��Ȃ�B
					if (collision->IsHit(m_collisionObject) == true && m_bounce <= 3)
					{
						m_bounce++;
						m_deletetimer = 0.0f;
					}
				}
			}
			Move();
			//�X�V�����B
			m_modelRender.Update();
		}
	}
}

void Attack::Move()
{
	if (m_attackno == 0)
	{
		//�e�̍��W��movespeed��+���Ă���āA�e�𓮂����B
		m_position += m_moveSpeed * 10.0f;
		m_modelRender.SetPosition(m_position);
		//setposition�œ������e�̓����蔻��̔��f
		m_collisionObject->SetPosition(m_position);
		//�v���C���[�̍��W�ƒe�̋����̃x�N�g�������߂�B
		Vector3 diff = m_playerposition - m_position;

		//��������Ă���5�b�o�߂�����
		if (m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackno == 1)
	{
		m_position.y -= 5.0f;

		if (m_position.y <= 5.0f)
		{
			m_position.y = 5.0f;
		}
		m_modelRender.SetPosition(m_position);
		m_collisionObject->SetPosition(m_position);
		m_modelRender.Update();
		//��������Ă���5�b�o�߂�����
		if (m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackno == 2)
	{

		//��������Ă���5�b�o�߂�����
		if (m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackno ==3)
	{
		//���˂�����0,2�Ȃ�e�̍��W��movespeed��+���Ă���āA�e�𓮂����B
		if (m_bounce == 0 || m_bounce == 2)
		{
			m_position += m_moveSpeed * 15.0f;
		}
		//���˂�����1,3�Ȃ�e�̍��W��movespeed��-���Ă���āA�e�𓮂����B
		if (m_bounce == 1 || m_bounce >= 3)
		{
			m_position -= m_moveSpeed * 15.0f;
		}
		m_rotation.AddRotationY(50.0f);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.SetPosition(m_position);
		//setposition�œ������e�̓����蔻��̔��f
		m_collisionObject->SetPosition(m_position);
		m_collisionObject->SetRotation(m_rotation);
		//�v���C���[�̍��W�ƒe�̋����̃x�N�g�������߂�B
		Vector3 diff = m_playerposition - m_position;

		//5�b�o�߂��Ă��邩�A�o�E���h����3��ȏ�Ȃ�
		if (m_bounce >= 4|| m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
}

void Attack::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}