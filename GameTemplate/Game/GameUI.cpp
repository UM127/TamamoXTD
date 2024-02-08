#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"
#include "PlayerLevelManagement.h"

bool GameUI::Start()
{
	m_plmanager = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_playericon.Init("Assets/sprite/PLAYERicon.dds", 120.0f, 120.0f);
	m_playericon.SetPosition({ -730.0f,380.0f,0.0f });
	m_playericon.Update();
	m_pistolsprite.Init("Assets/sprite/Pistol.dds", 90.0f, 90.0f);
	m_pistolsprite.SetPosition({ -610.0f,390.0f,0.0f });
	m_pistolsprite.Update();
	m_holywater.Init("Assets/sprite/Holywater.dds", 90.0f, 90.0f);
	m_holywater.SetPosition({ -495.0f,390.0f,0.0f });
	m_holywater.Update();
	m_mine.Init("Assets/sprite/mine.dds", 90.0f, 90.0f);
	m_mine.SetPosition({ -380.0f,390.0f,0.0f });
	m_mine.Update();
	m_boomerang.Init("Assets/sprite/boomerang.dds", 90.0f, 90.0f);
	m_boomerang.SetPosition({ -265.0f,390.0f,0.0f });
	m_boomerang.Update();
	m_levelup.Init("Assets/sprite/upgrade.dds", 720.0f, 720.0f);
	m_levelup.SetPosition({ 0.0f,0.0f,0.0f });
	m_levelup.Update();
	m_cursor.Init("Assets/sprite/cursor.dds", 50.0f, 50.0f);
	for (int i = 0; i < 5; i++)
	{
		m_pistolstarsprite[i].Init("Assets/sprite/star.dds", 40.0f, 40.0f);
	}
	m_pistolstarsprite[0].SetPosition({ -645.0f,320.0f,0.0f });
	m_pistolstarsprite[1].SetPosition({ -610.0f,320.0f,0.0f });
	m_pistolstarsprite[2].SetPosition({ -575.0f,320.0f,0.0f });
	m_pistolstarsprite[3].SetPosition({ -645.0f,280.0f,0.0f });
	m_pistolstarsprite[4].SetPosition({ -610.0f,280.0f,0.0f });
	for (int i = 0; i < 5; i++)
	{
		m_pistolstarsprite[i].Update();
	}
	//聖水UI
	for (int i = 0; i < 5; i++)
	{
		m_holystarsprite[i].Init("Assets/sprite/star.dds", 40.0f, 40.0f);
	}
	m_holystarsprite[0].SetPosition({ -530.0f,320.0f,0.0f });
	m_holystarsprite[1].SetPosition({ -495.0f,320.0f,0.0f });
	m_holystarsprite[2].SetPosition({ -460.0f,320.0f,0.0f });
	m_holystarsprite[3].SetPosition({ -530.0f,280.0f,0.0f });
	m_holystarsprite[4].SetPosition({ -495.0f,280.0f,0.0f });
	for (int i = 0; i < 5; i++)
	{
		m_holystarsprite[i].Update();
	}
	//地雷UI
	for (int i = 0; i < 5; i++)
	{
		m_minestarsprite[i].Init("Assets/sprite/star.dds", 40.0f, 40.0f);
	}
	m_minestarsprite[0].SetPosition({ -415.0f,320.0f,0.0f });
	m_minestarsprite[1].SetPosition({ -380.0f,320.0f,0.0f });
	m_minestarsprite[2].SetPosition({ -345.0f,320.0f,0.0f });
	m_minestarsprite[3].SetPosition({ -415.0f,280.0f,0.0f });
	m_minestarsprite[4].SetPosition({ -380.0f,280.0f,0.0f });
	for (int i = 0; i < 5; i++)
	{
		m_minestarsprite[i].Update();
	}
	//ブーメランUI
	for (int i = 0; i < 5; i++)
	{
		m_boomerangstarsprite[i].Init("Assets/sprite/star.dds", 40.0f, 40.0f);
	}
	m_boomerangstarsprite[0].SetPosition({ -300.0f,320.0f,0.0f });
	m_boomerangstarsprite[1].SetPosition({ -265.0f,320.0f,0.0f });
	m_boomerangstarsprite[2].SetPosition({ -230.0f,320.0f,0.0f });
	m_boomerangstarsprite[3].SetPosition({ -300.0f,280.0f,0.0f });
	m_boomerangstarsprite[4].SetPosition({ -265.0f,280.0f,0.0f });
	for (int i = 0; i < 5; i++)
	{
		m_boomerangstarsprite[i].Update();
	}
	return true;
}
void GameUI::Update()
{

	//もし世界が止まってるなら(ポーズなら)
	if (FindGO<Game>("game")->GetWorldStop() == true)
	{
		Pause();
	}
}
void GameUI::Pause()
{
	/// <summary>
	/// 4(ブーメラン)の時
	/// </summary>
	if (m_plmanager->GetPlayerSelectLevelUp() == 4)
	{
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			/// <summary>
			/// 0(強化しないにする)
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(0);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))
		{
			/// <summary>
			/// 3(聖水)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(3);
		}
	}
	/// <summary>
	/// 3(聖水の時)
	/// </summary>
	else if (m_plmanager->GetPlayerSelectLevelUp() == 3)
	{
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			/// <summary>
			/// 4(ブーメラン)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(4);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))
		{
			/// <summary>
			/// 2(地雷)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(2);
		}
	}

	/// <summary>
	/// 2(地雷の時)
	/// </summary>
	else if (m_plmanager->GetPlayerSelectLevelUp() == 2)
	{
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			/// <summary>
			/// 3(聖水)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(3);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))
		{
			/// <summary>
			/// 1(銃)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(1);
		}
	}

	/// <summary>
	/// 1(銃の時)
	/// </summary>
	else if (m_plmanager->GetPlayerSelectLevelUp() == 1)
	{
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			/// <summary>
			/// 2(地雷)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(2);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))
		{
			/// <summary>
			/// 0(強化しない)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(0);
		}
	}

	/// <summary>
	/// 0(強化しない)の時
	/// </summary>
	else if (m_plmanager->GetPlayerSelectLevelUp() == 0)
	{
		if (g_pad[0]->IsTrigger(enButtonDown))
		{
			/// <summary>
			/// 1(銃)にする
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(1);
		}
		else if (g_pad[0]->IsTrigger(enButtonUp))
		{
			/// <summary>
			/// 4(ブーメランにする)
			/// </summary>
			m_plmanager->SetPlayerSelectLevelUp(4);
		}
	}

	if (m_plmanager->GetPlayerSelectLevelUp() == 0)
	{
		m_cursor.SetPosition({ -235.0f,-210.0f,0.0f });
	}
	if (m_plmanager->GetPlayerSelectLevelUp() == 1)
	{
		m_cursor.SetPosition({ -295.0f,110.0f,0.0f });
	}
	if (m_plmanager->GetPlayerSelectLevelUp() == 2)
	{
		m_cursor.SetPosition({ -10.0f,110.0f,0.0f });
	}
	if (m_plmanager->GetPlayerSelectLevelUp() == 3)
	{
		m_cursor.SetPosition({ -295.0f,-55.0f,0.0f });
	}
	if (m_plmanager->GetPlayerSelectLevelUp() == 4)
	{
		m_cursor.SetPosition({ -10.0f,-55.0f,0.0f });
	}
	m_cursor.Update();

	if (m_plmanager->GetLevelUpFlag() == true)
	{
		 //<summary>
		 //強化しないでBボタンを押されたときPauseを解除する。
		 //</summary>
		if (m_plmanager->GetPlayerSelectLevelUp() == 0 && g_pad[0]->IsTrigger(enButtonB))
		{
			m_plmanager->SetLevelUpFlag(false);
		}
		/// <summary>
		/// 銃でBボタンを押されたときレベルを上げてPauseを解除する
		/// </summary>
		if (m_plmanager->GetPlayerSelectLevelUp() == 1 && g_pad[0]->IsTrigger(enButtonB))
		{
			/// <summary>
			/// 経験値が足りない場合早期リターンする。
			/// </summary>
			if (m_plmanager->GetEXP() < 5)
			{
				return;
			}
			/// <summary>
			/// 銃のレベルが5以上なら早期リターン
			/// </summary>
			if (m_plmanager->GetShotStageGun()>=5)
			{
				return;
			}
			m_plmanager->DownEXP(5);
			m_plmanager->AddShotStageGun();
			m_plmanager->SetLevelUpFlag(false);
		}
		/// <summary>
		/// 地雷でBボタンを押されたときレベルを上げてPauseを解除する
		/// </summary>
		if (m_plmanager->GetPlayerSelectLevelUp() == 2 && g_pad[0]->IsTrigger(enButtonB))
		{
			/// <summary>
			/// 経験値が足りない場合早期リターンする。
			/// </summary>
			if (m_plmanager->GetEXP() < 10)
			{
				return;
			}
			/// <summary>
			/// 地雷のレベルが5以上なら早期リターン
			/// </summary>
			if (m_plmanager->GetShotStageLandMine()>=5)
			{
				return;
			}
			m_plmanager->DownEXP(10);
			m_plmanager->AddShotStageLandMine();
			m_plmanager->SetLevelUpFlag(false);
		}
		/// <summary>
		/// 聖水でBボタンを押されたときレベルを上げてPauseを解除する
		/// </summary>
		if (m_plmanager->GetPlayerSelectLevelUp() == 3 && g_pad[0]->IsTrigger(enButtonB))
		{
			/// <summary>
			/// 経験値が足りない場合早期リターンする。
			/// </summary>
			if (m_plmanager->GetEXP() < 20)
			{
				return;
			}
			/// <summary>
			/// 聖水のレベルが5以上なら早期リターン
			/// </summary>
			if (m_plmanager->GetShotStageHolyWater()>=5)
			{
				return;
			}
			m_plmanager->DownEXP(20);
			m_plmanager->AddShotStageHolyWater();
			m_plmanager->SetLevelUpFlag(false);
		}
		/// <summary>
		/// ブーメランでBボタンを押されたときレベルを上げてPauseを解除する
		/// </summary>
		if (m_plmanager->GetPlayerSelectLevelUp() == 4 && g_pad[0]->IsTrigger(enButtonB))
		{
			/// <summary>
			/// 経験値が足りない場合早期リターンする。
			/// </summary>
			if (m_plmanager->GetEXP() < 30)
			{
				return;
			}
			/// <summary>
			/// ブーメランのレベルが5以上なら早期リターン
			/// </summary>
			if (m_plmanager->GetShotStageBoomerang() >= 5)
			{
				return;
			}
			m_plmanager->DownEXP(30);
			m_plmanager->AddShotStageBoomerang();
			m_plmanager->SetLevelUpFlag(false);
		}
	}
}
void GameUI::Render(RenderContext& rc)
{
	m_playericon.Draw(rc);
	m_pistolsprite.Draw(rc);
	m_holywater.Draw(rc);
	m_mine.Draw(rc);
	m_boomerang.Draw(rc);
	if (m_plmanager->GetShotStageGun() >= 1)
	{
		m_pistolstarsprite[0].Draw(rc);
	}
	if (m_plmanager->GetShotStageGun()>=2)
	{
		m_pistolstarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStageGun() >= 3)
	{
		m_pistolstarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStageGun() >= 4)
	{
		m_pistolstarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStageGun() >= 5)
	{
		m_pistolstarsprite[4].Draw(rc);
	}
	//聖水
	if (m_plmanager->GetShotStageHolyWater() >= 1)
	{
		m_holystarsprite[0].Draw(rc);
	}
	if (m_plmanager->GetShotStageHolyWater() >= 2)
	{
		m_holystarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStageHolyWater() >= 3)
	{
		m_holystarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStageHolyWater() >= 4)
	{
		m_holystarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStageHolyWater() >= 5)
	{
		m_holystarsprite[4].Draw(rc);
	}
	//地雷
	if (m_plmanager->GetShotStageLandMine() >= 1)
	{
		m_minestarsprite[0].Draw(rc);
	}
	if (m_plmanager->GetShotStageLandMine() >= 2)
	{
		m_minestarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStageLandMine() >= 3)
	{
		m_minestarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStageLandMine() >= 4)
	{
		m_minestarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStageLandMine() >= 5)
	{
		m_minestarsprite[4].Draw(rc);
	}
	//ブーメラン
	if (m_plmanager->GetShotStageBoomerang() >= 1)
	{
		m_boomerangstarsprite[0].Draw(rc);
	}
	if (m_plmanager->GetShotStageBoomerang() >= 2)
	{
		m_boomerangstarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStageBoomerang() >= 3)
	{
		m_boomerangstarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStageBoomerang() >= 4)
	{
		m_boomerangstarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStageBoomerang() >= 5)
	{
		m_boomerangstarsprite[4].Draw(rc);
	}

	if (m_plmanager->GetLevelUpFlag() == true)
	{
		m_levelup.Draw(rc);
		m_cursor.Draw(rc);
	}
}