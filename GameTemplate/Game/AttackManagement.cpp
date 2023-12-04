#include "stdafx.h"
#include "AttackManagement.h"
#include "Player.h"
#include "PlayerLevelManagement.h"
#include "Attack.h"

bool AttackManagement::Start()
{
	m_plmanager = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_player = FindGO<Player>("player");
	m_shotflag[0] = false;//’e
	m_shotflag[1] = false;//¹…
	m_shotflag[2] = false;
	m_shotflag[3] = false;
	return true;
}

void AttackManagement::Update()
{

	//•Ší‚ª—LŒø‰»‚³‚ê‚Ä‚¢‚ÄAUŒ‚‚ªI—¹‚µ‚½‚çƒ^ƒCƒ}[‚ğƒJƒEƒ“ƒg‚·‚é
	if (m_plmanager->GetWeaponFlag() == true)
	{
		//UŒ‚ì¬‚Ég‚¤ƒ^ƒCƒ}[‚Ìæ“¾
		m_attackmadetimer[0] += g_gameTime->GetFrameDeltaTime();
		m_attackmadetimer[1] += g_gameTime->GetFrameDeltaTime();
	}
	//’e
	if (m_plmanager->GetShotStage() == 5)
	{
		if (m_attackmadetimer[0] >= 0.25f && m_shotflag[0] == true)
		{
			m_shotflag[0] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 4)
	{
		if (m_attackmadetimer[0] >= 0.3f && m_shotflag[0] == true)
		{
			m_shotflag[0] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 3)
	{
		if (m_attackmadetimer[0] >= 0.4f && m_shotflag[0] == true)
		{
			m_shotflag[0] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 2)
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
	//¹…
	if (m_plmanager->GetShotStage() == 5)
	{
		if (m_attackmadetimer[1] >= 0.25f && m_shotflag[1] == true)
		{
			m_shotflag[1] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 4)
	{
		if (m_attackmadetimer[1] >= 0.3f && m_shotflag[1] == true)
		{
			m_shotflag[1] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 3)
	{
		if (m_attackmadetimer[1] >= 0.4f && m_shotflag[1] == true)
		{
			m_shotflag[1] = false;
		}
	}
	else if (m_plmanager->GetShotStage() == 2)
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

	AttackMade();
}

void AttackManagement::AttackMade()
{
	//’e
		if (m_plmanager->GetShotStage() == 1 && m_shotflag[0] == false)
		{
				//UŒ‚‚Ìì¬(’e)
				m_attack[0] = NewGO<Attack>(0, "attack");
				m_attack[0]->SetAttack(0);
				m_attack[0]->SetMoveSpeed(m_player->GetPlayerForward());
				m_shotflag[0] = true;
			m_attackmadetimer[0] = 0.0f;
		}
		if (m_plmanager->GetShotStage() == 2 && m_shotflag[0] == false)
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
		if (m_plmanager->GetShotStage() == 3 && m_shotflag[0] == false)
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
		if (m_plmanager->GetShotStage() == 4 && m_shotflag[0] == false)
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
		if (m_plmanager->GetShotStage() == 5 && m_shotflag[0] == false)
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
		if (m_plmanager->GetShotStage() == 1 && m_shotflag[1] == false)
		{
			//UŒ‚‚Ìì¬(¹…)
			m_attack[1] = NewGO<Attack>(0, "attack");
			m_attack[1]->SetAttack(1);
			m_attack[1]->SetMoveSpeed(m_player->GetPlayerForward());
			m_shotflag[1] = true;
			m_attackmadetimer[1] = 0.0f;
		}
		if (m_plmanager->GetShotStage() == 2 && m_shotflag[1] == false)
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
		if (m_plmanager->GetShotStage() == 3 && m_shotflag[1] == false)
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
		if (m_plmanager->GetShotStage() == 4 && m_shotflag[1] == false)
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
		if (m_plmanager->GetShotStage() == 5 && m_shotflag[1] == false)
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

}