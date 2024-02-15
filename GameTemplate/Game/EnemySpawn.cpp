#include "stdafx.h"
#include "EnemySpawn.h"
#include "Enemy.h"
#include "Game.h"
#include "Result.h"
bool EnemySpawn::Start()
{
	for (int o = 0; o < 25; o++)
	{
		Enemy* enemy = NewGO<Enemy>(0, "enemy");
	}
	return true;
}
void EnemySpawn::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		if (m_gametimer >= 120.0f)
		{
			FindGO<Game>("game")->SetResult(true);
		}
		//世界が止まっていないなら
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			m_gametimer += g_gameTime->GetFrameDeltaTime();
			m_spawntimer += g_gameTime->GetFrameDeltaTime();
			if (m_spawntimer >= 5.0f)
			{
				EnemySpawnManagement();
				m_spawntimer = 0.0f;
			}
			Font();
		}
		if (m_gametimer >= 90.0f)
		{
			m_enemyspawnstage = 3;
		}
		else if (m_gametimer >= 60.0f)
		{
			m_enemyspawnstage = 2;
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}
}
void EnemySpawn::EnemySpawnManagement()
{
	if (m_enemyspawnstage == 3)
	{
		for (int o = 0; o < 20; o++)
		{
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
		}
	}
	else if (m_enemyspawnstage == 2)
	{
		for (int o = 0; o < 15; o++)
		{
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
		}
	}
	else if (m_enemyspawnstage == 1)
	{
		for (int o = 0; o < 10; o++)
		{
			Enemy* enemy = NewGO<Enemy>(0, "enemy");
		}
	}

}
void EnemySpawn::Font()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%3d", int(m_gametimer));

	//表示するテキストを設定。
	m_fontrender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontrender.SetPosition(Vector3(-200.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontrender.SetScale(3.0f);
	//黒色に設定
	m_fontrender.SetColor(g_vec4White);
}
void EnemySpawn::Render(RenderContext& rc)
{
	if (m_setresultstop == false)
	{
		m_fontrender.Draw(rc);
	}
}