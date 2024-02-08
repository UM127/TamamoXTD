#include "stdafx.h"
#include "AttackManagement.h"
#include "Player.h"
#include "PlayerLevelManagement.h"
#include "Attack.h"
#include "Game.h"

bool AttackManagement::Start()
{
	m_plmanager = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_player = FindGO<Player>("player");
	m_shotflag[0] = false;//�e
	m_shotflag[1] = false;//����
	m_shotflag[2] = false;//�n��
	m_shotflag[3] = false;//�u�[������
	return true;
}

void AttackManagement::Update()
{
	//���E���~�܂��Ă��Ȃ��Ȃ�
	if (FindGO<Game>("game")->GetWorldStop() == false)
	{
		//���킪�L��������Ă��āA�U�����I��������^�C�}�[���J�E���g����
		if (m_plmanager->GetWeaponFlag() == true)
		{
			//�U���쐬�Ɏg���^�C�}�[�̎擾
			m_attackmadetimer[0] += g_gameTime->GetFrameDeltaTime();
			m_attackmadetimer[1] += g_gameTime->GetFrameDeltaTime();
			m_attackmadetimer[2] += g_gameTime->GetFrameDeltaTime();
			m_attackmadetimer[3] += g_gameTime->GetFrameDeltaTime();
		}
		//�e
		if (m_plmanager->GetShotStageGun() == 5)
		{
			if (m_attackmadetimer[0] >= 0.25f && m_shotflag[0] == true)
			{
				m_shotflag[0] = false;
			}
		}
		else if (m_plmanager->GetShotStageGun() == 4)
		{
			if (m_attackmadetimer[0] >= 0.3f && m_shotflag[0] == true)
			{
				m_shotflag[0] = false;
			}
		}
		else if (m_plmanager->GetShotStageGun() == 3)
		{
			if (m_attackmadetimer[0] >= 0.4f && m_shotflag[0] == true)
			{
				m_shotflag[0] = false;
			}
		}
		else if (m_plmanager->GetShotStageGun() == 2)
		{
			if (m_attackmadetimer[0] >= 0.45f && m_shotflag[0] == true)
			{
				m_shotflag[0] = false;
			}
		}
		else if (m_attackmadetimer[0] >= 0.5f && m_shotflag[0] == true)
		{
			m_shotflag[0] = false;
		}
		//����
		if (m_plmanager->GetShotStageHolyWater() == 5)
		{
			if (m_attackmadetimer[1] >= 0.25f && m_shotflag[1] == true)
			{
				m_shotflag[1] = false;
			}
		}
		else if (m_plmanager->GetShotStageHolyWater() == 4)
		{
			if (m_attackmadetimer[1] >= 0.3f && m_shotflag[1] == true)
			{
				m_shotflag[1] = false;
			}
		}
		else if (m_plmanager->GetShotStageHolyWater() == 3)
		{
			if (m_attackmadetimer[1] >= 0.4f && m_shotflag[1] == true)
			{
				m_shotflag[1] = false;
			}
		}
		else if (m_plmanager->GetShotStageHolyWater() == 2)
		{
			if (m_attackmadetimer[1] >= 0.45f && m_shotflag[1] == true)
			{
				m_shotflag[1] = false;
			}
		}
		else if (m_attackmadetimer[1] >= 0.5f && m_shotflag[1] == true)
		{
			m_shotflag[1] = false;
		}
		//�n��
		if (m_plmanager->GetShotStageLandMine() == 5)
		{
			if (m_attackmadetimer[2] >= 1.00f && m_shotflag[2] == true)
			{
				m_shotflag[2] = false;
			}
		}
		else if (m_plmanager->GetShotStageLandMine() == 4)
		{
			if (m_attackmadetimer[2] >= 1.25f && m_shotflag[2] == true)
			{
				m_shotflag[2] = false;
			}
		}
		else if (m_plmanager->GetShotStageLandMine() == 3)
		{
			if (m_attackmadetimer[2] >= 1.5f && m_shotflag[2] == true)
			{
				m_shotflag[2] = false;
			}
		}
		else if (m_plmanager->GetShotStageLandMine() == 2)
		{
			if (m_attackmadetimer[2] >= 1.75f && m_shotflag[2] == true)
			{
				m_shotflag[2] = false;
			}
		}
		else if (m_attackmadetimer[2] >= 2.0f && m_shotflag[2] == true)
		{
			m_shotflag[2] = false;
		}

		//�u�[������
		if (m_plmanager->GetShotStageBoomerang() == 5)
		{
			if (m_attackmadetimer[3] >= 0.25f && m_shotflag[3] == true)
			{
				m_shotflag[3] = false;
			}
		}
		else if (m_plmanager->GetShotStageBoomerang() == 4)
		{
			if (m_attackmadetimer[3] >= 0.3f && m_shotflag[3] == true)
			{
				m_shotflag[3] = false;
			}
		}
		else if (m_plmanager->GetShotStageBoomerang() == 3)
		{
			if (m_attackmadetimer[3] >= 0.4f && m_shotflag[3] == true)
			{
				m_shotflag[3] = false;
			}
		}
		else if (m_plmanager->GetShotStageBoomerang() == 2)
		{
			if (m_attackmadetimer[3] >= 0.45f && m_shotflag[3] == true)
			{
				m_shotflag[3] = false;
			}
		}
		else if (m_attackmadetimer[3] >= 0.5f && m_shotflag[3] == true)
		{
			m_shotflag[3] = false;
		}

		AttackMade();
	}
}

void AttackManagement::AttackMade()
{
	//�e
		if (m_plmanager->GetShotStageGun() == 1 && m_shotflag[0] == false)
		{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
				m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStageGun() == 2 && m_shotflag[0] == false)
		{
			if (m_shotflag[0] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStageGun() == 3 && m_shotflag[0] == false)
		{
			if (m_shotflag[0] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStageGun() == 4 && m_shotflag[0] == false)
		{
			if (m_shotflag[0] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStageGun() == 5 && m_shotflag[0] == false)
		{
			if (m_shotflag[0] == false)
			{
				//�U���̍쐬(�e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		//����
		if (m_plmanager->GetShotStageHolyWater() == 1 && m_shotflag[1] == false)
		{
			//�U���̍쐬(����)
			m_attack[1] = NewGO<Attack>(0, "attack");
			m_attack[1]->SetAttack(1);
			m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
			m_shotflag[1] = true;
			m_attackmadetimer[1] = 0.0f;
		}
		if (m_plmanager->GetShotStageHolyWater() == 2 && m_shotflag[1] == false)
		{
			if (m_shotflag[1] == false)
			{
				//�U���̍쐬(����)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		if (m_plmanager->GetShotStageHolyWater() == 3 && m_shotflag[1] == false)
		{
			if (m_shotflag[1] == false)
			{
				//�U���̍쐬(����)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		if (m_plmanager->GetShotStageHolyWater() == 4 && m_shotflag[1] == false)
		{
			if (m_shotflag[1] == false)
			{
				//�U���̍쐬(����)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		if (m_plmanager->GetShotStageHolyWater() == 5 && m_shotflag[1] == false)
		{
			if (m_shotflag[1] == false)
			{
				//�U���̍쐬(����)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		//�n��
		if (m_plmanager->GetShotStageLandMine() == 1 && m_shotflag[2] == false)
		{
			//�U���̍쐬(�n��)
			m_attack[2] = NewGO<Attack>(0, "attack");
			m_attack[2]->SetAttack(2);
			m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
			m_shotflag[2] = true;
			m_attackmadetimer[2] = 0.0f;
		}
		if (m_plmanager->GetShotStageLandMine() == 2 && m_shotflag[2] == false)
		{
			if (m_shotflag[2] == false)
			{
				//�U���̍쐬(�n��)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		if (m_plmanager->GetShotStageLandMine() == 3 && m_shotflag[2] == false)
		{
			if (m_shotflag[2] == false)
			{
				//�U���̍쐬(�n��)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		if (m_plmanager->GetShotStageLandMine() == 4 && m_shotflag[2] == false)
		{
			if (m_shotflag[2] == false)
			{
				//�U���̍쐬(�n��)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		if (m_plmanager->GetShotStageLandMine() == 5 && m_shotflag[2] == false)
		{
			if (m_shotflag[2] == false)
			{
				//�U���̍쐬(�n��)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		//�u�[������
		if (m_plmanager->GetShotStageBoomerang() == 1 && m_shotflag[3] == false)
		{
			//�U���̍쐬(�e)
			m_attack[3] = NewGO<Attack>(0, "attack");
			m_attack[3]->SetAttack(3);
			m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
			m_shotflag[3] = true;
			m_attackmadetimer[3] = 0.0f;
		}
		if (m_plmanager->GetShotStageBoomerang() == 2 && m_shotflag[3] == false)
		{
			if (m_shotflag[3] == false)
			{
				//�U���̍쐬(�e)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
		if (m_plmanager->GetShotStageBoomerang() == 3 && m_shotflag[3] == false)
		{
			if (m_shotflag[3] == false)
			{
				//�U���̍쐬(�e)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
		if (m_plmanager->GetShotStageBoomerang() == 4 && m_shotflag[3] == false)
		{
			if (m_shotflag[3] == false)
			{
				//�U���̍쐬(�e)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
		if (m_plmanager->GetShotStageBoomerang() == 5 && m_shotflag[3] == false)
		{
			if (m_shotflag[3] == false)
			{
				//�U���̍쐬(�e)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
}