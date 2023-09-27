#include "stdafx.h"
#include "AttackManagement.h"
#include "Player.h"
#include "PlayerLevelManagement.h"
#include "Attack.h"

bool AttackManagement::Start()
{
	m_plmanager = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_player = FindGO<Player>("player");
	m_shotflag[0] = false;
	m_shotflag[1] = false;
	m_shotflag[2] = false;
	m_shotflag[3] = false;
	return true;
}

void AttackManagement::Update()
{

	//���킪�L��������Ă��āA�U�����I��������^�C�}�[���J�E���g����
	if (m_plmanager->GetWeaponFlag() == true)
	{
		//�U���쐬�Ɏg���^�C�}�[�̎擾
		m_attackmadetimer[0] += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackmadetimer[0] >= 1.0f&& m_shotflag[0] == true)
	{
		m_shotflag[0] = false;
	}
	AttackMade();
}

void AttackManagement::AttackMade()
{
		if (m_plmanager->GetShotStage() == 1 && m_shotflag[0] == false)
		{
			int i;
			for (int o = 0; o < 2; ++o)
			{
				//�U���̍쐬(�e)
				m_attack[o] = NewGO<Attack>(0, "attack");
				m_attack[o]->SetAttack(0);
				m_attack[o]->SetMoveSpeed(m_player->GetPlayerForward());
				m_attack[o]->SetSide(m_player->GetSideVector());
				if (o == 0)
				{
					m_attack[o]->SetAttackA(0);
				}
				if (o == 1)
				{
					m_attack[o]->SetAttackA(1);
				}
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStage() == 2)
		{
			if (m_shotflag[0] == false&& m_shotflag[1] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			if (m_shotflag[1] == true&& m_attackmadetimer[0] >= 1.2f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_attackmadetimer[0] = 0.0f;
				m_shotflag[1] = false;
				m_shotflag[0] = true;
			}
		}
		if (m_plmanager->GetShotStage() == 3)
		{
			if (m_shotflag[0] == false && m_shotflag[1] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			if (m_shotflag[1] == true && m_shotflag[2]==false&& m_attackmadetimer[0] >= 1.2f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			if (m_shotflag[2] == true && m_attackmadetimer[0] >= 1.4f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_attackmadetimer[0] = 0.0f;
				m_shotflag[1] = false;
				m_shotflag[2] = false;
				m_shotflag[0] = true;
			}
		}
		if (m_plmanager->GetShotStage() == 4)
		{
			if (m_shotflag[0] == false && m_shotflag[1] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			if (m_shotflag[1] == true && m_shotflag[2] == false && m_attackmadetimer[0] >= 1.2f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			if (m_shotflag[2] == true && m_shotflag[3] == false && m_attackmadetimer[0] >= 1.4f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			if (m_shotflag[3] == true && m_attackmadetimer[0] >= 1.6f)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_attackmadetimer[0] = 0.0f;
				m_shotflag[1] = false;
				m_shotflag[2] = false;
				m_shotflag[3] = false;
				m_shotflag[0] = true;
			}
		}
}