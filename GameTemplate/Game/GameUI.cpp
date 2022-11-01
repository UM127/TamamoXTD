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
	for (int i = 0; i < 4; i++)
	{
		m_starsprite[i].Init("Assets/sprite/star.dds", 40.0f, 40.0f);
	}
	m_starsprite[0].SetPosition({ -640.0f,320.0f,0.0f });
	m_starsprite[1].SetPosition({ -600.0f,320.0f,0.0f });
	m_starsprite[2].SetPosition({ -560.0f,320.0f,0.0f });
	m_starsprite[3].SetPosition({ -640.0f,280.0f,0.0f });
	for (int i = 0; i < 4; i++)
	{
		m_starsprite[i].Update();
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
	m_starsprite[0].Draw(rc);
	if (m_plmanager->GetShotStage()>=2)
	{
		m_starsprite[1].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 3)
	{
		m_starsprite[2].Draw(rc);
	}
	if (m_plmanager->GetShotStage() >= 4)
	{
		m_starsprite[3].Draw(rc);
	}
}