#include "stdafx.h"
#include "EXP.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerLevelManagement.h"
#include "Game.h"
#include "Score.h"
//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

bool EXP::Start()
{
	m_player = FindGO<Player>("player");
	m_plmanagement = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_exp.Init("Assets/modelData/model/EXP.tkm", false);
	m_exposition.y = 20.0f;
	m_exp.SetScale(0.5f, 0.5f, 0.5f);
	m_exp.SetRotation(m_exrotation);
	m_exp.SetPosition(m_exposition);
	m_exp.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//Box��̃R���W�������쐬����B
	m_collisionObject->CreateBox(m_exposition,       //���W�B
		Quaternion::Identity,                                   //��]�B
		{ 20.0f,20.0f,20.0f });                                                //Box�̑傫���B
	//���O��t����B
	m_collisionObject->SetName("exp");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}
void EXP::Update()
{
	//���E���~�܂��Ă��Ȃ��Ȃ�
	if (FindGO<Game>("game") != NULL)
	{
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			Rotation();
			EXPProcess();
			//���f���̍X�V�����B
			m_exp.Update();
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}
}
void EXP::Rotation()
{
	m_exrotation.AddRotationY(0.01f);
	m_exp.SetRotation(m_exrotation);
	m_exp.Update();
}
void EXP::EXPProcess()
{
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_plmanagement->AddEXP();
		//�Փ˂��Ă�����B
		DeleteGO(m_collisionObject);
		DeleteGO(this);
	}
}

void EXP::Render(RenderContext& rc)
{
		m_exp.Draw(rc);
}