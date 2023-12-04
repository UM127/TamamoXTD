#include "stdafx.h"
#include "GameUI.h"
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
	//¹…UI
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
	return true;
}
void GameUI::Update()
{

}
void GameUI::Render(RenderContext& rc)
{
	m_playericon.Draw(rc);
	m_pistolsprite.Draw(rc);
	m_holywater.Draw(rc);
	m_pistolstarsprite[0].Draw(rc);
	if (m_plmanager->GetShotStage()>=2)
	{
		m_pistolstarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 3)
	{
		m_pistolstarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 4)
	{
		m_pistolstarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 5)
	{
		m_pistolstarsprite[4].Draw(rc);
	}
	//¹…
	m_holystarsprite[0].Draw(rc);
	if (m_plmanager->GetShotStage() >= 2)
	{
		m_holystarsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 3)
	{
		m_holystarsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 4)
	{
		m_holystarsprite[3].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 5)
	{
		m_holystarsprite[4].Draw(rc);
	}
}