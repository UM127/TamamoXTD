#include "stdafx.h"
#include "EnemySpawn.h"
#include "Enemy.h"
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
	m_gametimer += g_gameTime->GetFrameDeltaTime();
	m_spawntimer += g_gameTime->GetFrameDeltaTime();
	if (m_spawntimer >= 5.0f)
	{
		EnemySpawnManagement();
		m_spawntimer = 0.0f;
	}
	Font();
}
void EnemySpawn::EnemySpawnManagement()
{
	for (int o = 0; o < 5; o++)
	{
		Enemy* enemy = NewGO<Enemy>(0, "enemy");
	}


}
void EnemySpawn::Font()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%3d", int(m_gametimer));

	//�\������e�L�X�g��ݒ�B
	m_fontrender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontrender.SetPosition(Vector3(-200.0f, 500.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontrender.SetScale(3.0f);
	//���F�ɐݒ�
	m_fontrender.SetColor(g_vec4White);
}
void EnemySpawn::Render(RenderContext& rc)
{
	m_fontrender.Draw(rc);
}