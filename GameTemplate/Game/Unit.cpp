#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"


bool Unit::Start()
{
	m_player = FindGO<Player>("player");

	//���f���̓ǂݍ���
	m_attackcircle.Init("Assets/modelData/AttackCircle.tkm");

	if (m_characterNo == 0)
	{
		////�A�j���[�V������ǂݍ���
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/Vanguard/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/Vanguard/Vanguard.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	if (m_characterNo == 1) {
		////�A�j���[�V������ǂݍ���
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/ElyByK/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/ElyByK/ElyByK.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	if (m_characterNo == 2) {
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/HerakliosByADizon/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/HerakliosByADizon/HerakliosByADizon.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	m_attackcircle.SetScale({ 7.5f,1.0f,7.5f });
	m_attackcircle.SetPosition(m_position);
	m_attackcircle.Update();
	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	//�J�v�Z����̃R���W�������쐬����B
	m_collisionObject->CreateCapsule(m_position,       //���W�B
		Quaternion::Identity,                                   //��]�B
		75.0f,													//���̑傫��(���a)�B
		1.0f);                                                //���̑傫��(����)�B
		//���O��t����B
	m_collisionObject->SetName("attackcircle");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_unit.SetRotation(m_rotation);
	m_unit.SetPosition(m_position);
	m_unit.Update();

	return true;
}

void Unit::Update()
{
	if (m_SetUp == true)
	{
		DeleteGO(this);
	}
	m_unit.SetPosition(m_position);
	m_unit.SetRotation(m_rotation);
	m_unit.Update();
}



void Unit::Render(RenderContext& rc)
{
	m_unit.Draw(rc);
	m_attackcircle.Draw(rc);
}
