#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include "GameUI.h"

bool Game::Start()
{

	//m_spriteRender.Init("Assets/sprite/gameclear.dds", 300.0f, 200.0f);

	/*m_spriteHP.Init("Assets/sprite/hpbar.dds", 300.0f, 200.0f);
	m_spriteHP.SetPivot(Vector2(0.0f, 0.5f));
	m_spriteHP.SetPosition(Vector3(-150.0f, 200.0f, 0.0f));
	m_spriteHP.Update();*/

	//for (int uni = 0; uni < 3; uni++) {
	//	m_unit = NewGO<Unit>(0, "unit");
	//	//���j�b�g�^�C�v�̂��̂���������B
	//	m_unit->SetUnitTipe(uni);
	//	m_unit->SetFirstsetup(true);
	//}
	//m_modelRender.Init("Assets/modelData/debug/teapot.tkm");
	//m_modelRender.ShadowInit("Assets/modelData/debug/teapot.tkm");
	//m_modelRender.SetPosition(0.0f, 50.0f, 0.0f);
	//m_modelRender.Update();
	//�v���C���[�I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player>(0, "player");
	//�G�l�~�[�o���̊Ǘ�������N���X
	m_enemyspawn = NewGO<EnemySpawn>(0, "enemyspawn");
	//�w�i�I�u�W�F�N�g���쐬����B
	m_background = NewGO<BackGround>(0, "background");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//�Q�[��UI�̐���
	m_gameui = NewGO<GameUI>(0, "gameui");
	return true;
}
void Game::Update()
{
	// ���X�e�B�b�N(�L�[�{�[�h�FWASD)�ŕ��s�ړ��B
	//m_pointligpos.x += g_pad[0]->GetLStickXF();
	//m_pointligpos.y += g_pad[0]->GetLStickYF();
	//g_directionLig.SetPointPos(m_pointligpos);
	//m_pointligpos.z += g_pad[0]->GetLStickYF();
	//m_pointligpos.y = 50.0f;
	//g_Lig.SetPointPos(m_pointligpos);
	///*
	////�f�B���N�V�������C�g�̓���������ƃJ���[���Z�b�g�ł����Ⴂ�܂�
	//g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	//g_directionLig.SetLigColor({ 0.5f,0.5f,0.5f });
	//*/
	//g_Lig.SetPointPos(m_pointligpos);

	//
	//g_Lig.SetPointColor({ 0.0f,0.0f,0.0f });

	//m_spPosition.x = 0.0f;
	//g_Lig.SetSpotPos(m_spPosition);//�X�|�b�g���C�g�̈ʒu��ݒ�


	////A�{�^������������,�������B
	//if (g_pad[0]->IsPress(enButtonA))
	//{
	//	m_directionligColor.x +=0.1f;
	//	m_directionligColor.y += 0.1f;
	//	m_directionligColor.z += 0.1f;
	//}
	////B�{�^������������A�������B
	//else if (g_pad[0]->IsPress(enButtonB))
	//{
	//	m_directionligColor.x -= 0.1f;
	//	m_directionligColor.y -= 0.1f;
	//	m_directionligColor.z -= 0.1f;
	//}
	//m_directionligColor.x = 1.5f;
	//m_directionligColor.y = 1.5f;
	//m_directionligColor.z = 1.5f;
	//g_Lig.SetLigColor({ m_directionligColor });

	//HP��0��茸���Ă�����B
	if (m_hp < 0)
	{
		//HP��0�ɂ���B
		m_hp = 0;
	}
	Vector3 scale = Vector3::One;
	scale.x = float(m_hp) / float(m_Maxhp);

	m_spriteHP.SetScale(scale);

	//�X�V�����B
	m_spriteHP.Update();
}
void Game::Render(RenderContext& rc)
{
	//m_spriteRender.Draw(rc);                 //�^�C�g���̕`��
	//m_spriteHP.Draw(rc);
	//m_fontRender.Draw(rc);
	m_modelRender.Draw(rc);
}