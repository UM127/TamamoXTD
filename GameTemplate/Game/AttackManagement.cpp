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
	m_shotflag[0] = false;//’e
	m_shotflag[1] = false;//¹…
	m_shotflag[2] = false;//’n—‹
	m_shotflag[3] = false;//ƒu[ƒƒ‰ƒ“
	return true;
}

void AttackManagement::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		//¢ŠE‚ª~‚Ü‚Á‚Ä‚¢‚È‚¢‚È‚ç
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			//•Ší‚ª—LŒø‰»‚³‚ê‚Ä‚¢‚ÄAUŒ‚‚ªI—¹‚µ‚½‚çƒ^ƒCƒ}[‚ğƒJƒEƒ“ƒg‚·‚é
			if (m_plmanager->GetWeaponFlag() == true)
			{
				//UŒ‚ì¬‚Ég‚¤ƒ^ƒCƒ}[‚Ìæ“¾
				m_attackmadetimer[0] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[1] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[2] += g_gameTime->GetFrameDeltaTime();
				m_attackmadetimer[3] += g_gameTime->GetFrameDeltaTime();
			}
			//’e
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
			//¹…
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
			//’n—‹
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

			//ƒu[ƒƒ‰ƒ“
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
	//’e
		if (m_plmanager->GetShotStageGun() == 1 && m_shotflag[0] == false)
		{
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			}
			m_attackmadetimer[0] = 0.0f;
		}
		//¹…
		if (m_plmanager->GetShotStageHolyWater() == 1 && m_shotflag[1] == false)
		{
			//UŒ‚‚Ìì¬(¹…)
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
				//UŒ‚‚Ìì¬(¹…)
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
				//UŒ‚‚Ìì¬(¹…)
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
				//UŒ‚‚Ìì¬(¹…)
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
				//UŒ‚‚Ìì¬(¹…)
				m_attack[1] = NewGO<Attack>(0, "attack");
				m_attack[1]->SetAttack(1);
				m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[1] = true;
			}
			m_attackmadetimer[1] = 0.0f;
		}
		//’n—‹
		if (m_plmanager->GetShotStageLandMine() == 1 && m_shotflag[2] == false)
		{
			//UŒ‚‚Ìì¬(’n—‹)
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
				//UŒ‚‚Ìì¬(’n—‹)
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
				//UŒ‚‚Ìì¬(’n—‹)
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
				//UŒ‚‚Ìì¬(’n—‹)
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
				//UŒ‚‚Ìì¬(’n—‹)
				m_attack[2] = NewGO<Attack>(0, "attack");
				m_attack[2]->SetAttack(2);
				m_attack[2]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[2] = true;
			}
			m_attackmadetimer[2] = 0.0f;
		}
		//ƒu[ƒƒ‰ƒ“
		if (m_plmanager->GetShotStageBoomerang() == 1 && m_shotflag[3] == false)
		{
			//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
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
				//UŒ‚‚Ìì¬(’e)
				m_attack[3] = NewGO<Attack>(0, "attack");
				m_attack[3]->SetAttack(3);
				m_attack[3]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[3] = true;
			}
			m_attackmadetimer[3] = 0.0f;
		}
}