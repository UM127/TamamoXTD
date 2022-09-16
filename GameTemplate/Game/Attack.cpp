#include "stdafx.h"
#include "Attack.h"
#include "Player.h"

//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"
//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "graphics/effect/EffectEmitter.h"

bool Attack::Start()
{
	//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
	m_position = FindGO<Player>("player")->GetPlayerPosition();
	m_position.y += 70.0f;
	m_playerposition = FindGO<Player>("player")->GetPlayerPosition();

		//�e�̃��f����ǂݍ��ށB
		m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm");
		m_modelRender.SetScale({ 0.2f,0.2f,0.2f });
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
		m_collisionObject->CreateSphere(collisionPosition,       //���W�B
			Quaternion::Identity,                                   //��]�B
			30.0f);                                                //���̑傫��(���a)�B
			//���O��t����B
		m_collisionObject->SetName("SoysauceAttack");
		//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
		m_collisionObject->SetIsEnableAutoDelete(false);
	
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
	Move();
	//�X�V�����B
	m_modelRender.Update();
}

void Attack::Move()
{
	//�e�̍��W��movespeed��+���Ă���āA�e�𓮂����B
	m_position += m_moveSpeed * 15.0f;
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

void Attack::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}