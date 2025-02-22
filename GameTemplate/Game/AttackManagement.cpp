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
	m_shotflag[0] = false;//弾
	m_shotflag[1] = false;//聖水
	m_shotflag[2] = false;//地雷
	m_shotflag[3] = false;//ブーメラン
	return true;
}

void AttackManagement::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		//世界が止まっていないなら
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			//武器が有効化されていて、攻撃が終了したらタイマーをカウントする
			if (m_plmanager->GetWeaponFlag() == true)
			{
				//攻撃作成に使うタイマーの取得
				m_attackmadetimer[0] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[1] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[2] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[3] += g_gameTime->GetFrameDeltaTime();
			}
			//弾
			if (m_plmanager->GetShotStageGun() == 5)
			{
				if (m_attackmadetimer[0] >= 0.3f && m_shotflag[0] == true)
				{
					m_shotflag[0] = false;
				}
			}
			else if (m_plmanager->GetShotStageGun() == 4)
			{
				if (m_attackmadetimer[0] >= 0.4f && m_shotflag[0] == true)
				{
					m_shotflag[0] = false;
				}
			}
			else if (m_plmanager->GetShotStageGun() == 3)
			{
				if (m_attackmadetimer[0] >= 0.5f && m_shotflag[0] == true)
				{
					m_shotflag[0] = false;
				}
			}
			else if (m_plmanager->GetShotStageGun() == 2)
			{
				if (m_attackmadetimer[0] >= 0.6f && m_shotflag[0] == true)
				{
					m_shotflag[0] = false;
				}
			}
			else if (m_attackmadetimer[0] >= 0.7f && m_shotflag[0] == true)
			{
				m_shotflag[0] = false;
			}
			//聖水
			if (m_plmanager->GetShotStageHolyWater() == 5)
			{
				if (m_attackmadetimer[1] >= 0.7f && m_shotflag[1] == true)
				{
					m_shotflag[1] = false;
				}
			}
			else if (m_plmanager->GetShotStageHolyWater() == 4)
			{
				if (m_attackmadetimer[1] >= 0.9f && m_shotflag[1] == true)
				{
					m_shotflag[1] = false;
				}
			}
			else if (m_plmanager->GetShotStageHolyWater() == 3)
			{
				if (m_attackmadetimer[1] >= 1.2f && m_shotflag[1] == true)
				{
					m_shotflag[1] = false;
				}
			}
			else if (m_plmanager->GetShotStageHolyWater() == 2)
			{
				if (m_attackmadetimer[1] >= 1.5f && m_shotflag[1] == true)
				{
					m_shotflag[1] = false;
				}
			}
			else if (m_attackmadetimer[1] >= 0.5f && m_shotflag[1] == true)
			{
				m_shotflag[1] = false;
			}
			//地雷
			if (m_plmanager->GetShotStageLandMine() == 5)
			{
				if (m_attackmadetimer[2] >= 2.00f && m_shotflag[2] == true)
				{
					m_shotflag[2] = false;
				}
			}
			else if (m_plmanager->GetShotStageLandMine() == 4)
			{
				if (m_attackmadetimer[2] >= 2.5f && m_shotflag[2] == true)
				{
					m_shotflag[2] = false;
				}
			}
			else if (m_plmanager->GetShotStageLandMine() == 3)
			{
				if (m_attackmadetimer[2] >= 3.0f && m_shotflag[2] == true)
				{
					m_shotflag[2] = false;
				}
			}
			else if (m_plmanager->GetShotStageLandMine() == 2)
			{
				if (m_attackmadetimer[2] >= 3.5f && m_shotflag[2] == true)
				{
					m_shotflag[2] = false;
				}
			}
			else if (m_attackmadetimer[2] >= 4.0f && m_shotflag[2] == true)
			{
				m_shotflag[2] = false;
			}

			//ブーメラン
			if (m_plmanager->GetShotStageBoomerang() == 5)
			{
				if (m_attackmadetimer[3] >= 0.3f && m_shotflag[3] == true)
				{
					m_shotflag[3] = false;
				}
			}
			else if (m_plmanager->GetShotStageBoomerang() == 4)
			{
				if (m_attackmadetimer[3] >= 0.4f && m_shotflag[3] == true)
				{
					m_shotflag[3] = false;
				}
			}
			else if (m_plmanager->GetShotStageBoomerang() == 3)
			{
				if (m_attackmadetimer[3] >= 0.5f && m_shotflag[3] == true)
				{
					m_shotflag[3] = false;
				}
			}
			else if (m_plmanager->GetShotStageBoomerang() == 2)
			{
				if (m_attackmadetimer[3] >= 0.75f && m_shotflag[3] == true)
				{
					m_shotflag[3] = false;
				}
			}
			else if (m_attackmadetimer[3] >= 1.0f && m_shotflag[3] == true)
			{
				m_shotflag[3] = false;
			}

			AttackMade();
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}
}

void AttackManagement::AttackMade()
{
	//弾
		if (m_plmanager->GetShotStageGun() == 1 && m_shotflag[0] == false)
		{
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		//聖水
		if (m_plmanager->GetShotStageHolyWater() == 1 && m_shotflag[1] == false)
		{
			//攻撃の作成(聖水)
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
				//攻撃の作成(聖水)
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
				//攻撃の作成(聖水)
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
				//攻撃の作成(聖水)
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
				//攻撃の作成(聖水)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		//地雷
		if (m_plmanager->GetShotStageLandMine() == 1 && m_shotflag[2] == false)
		{
			//攻撃の作成(地雷)
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
				//攻撃の作成(地雷)
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
				//攻撃の作成(地雷)
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
				//攻撃の作成(地雷)
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
				//攻撃の作成(地雷)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		//ブーメラン
		if (m_plmanager->GetShotStageBoomerang() == 1 && m_shotflag[3] == false)
		{
			//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
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
				//攻撃の作成(弾)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
}