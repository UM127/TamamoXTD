#include "stdafx.h"
#include "PlayerLevelManagement.h"

bool PlayerLevelManagement::Start()
{
	m_shotattackstage = 1;
	return true;
}
void PlayerLevelManagement::Font()
{
	int a = m_exp;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"EXP%d", a);

	//表示するテキストを設定。
	m_fontRender2.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender2.SetPosition(Vector3(400.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender2.SetScale(2.0f);
	//黒色に設定
	m_fontRender2.SetColor(g_vec4White);

	int b = m_shotattackstage;
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"しょっとれべる%d", b);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-900.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.0f);
	//黒色に設定
	m_fontRender.SetColor(g_vec4White);
}
void PlayerLevelManagement::Update()
{
	//描画処理。
	Font();

	//レベル処理。
	LevelManage();
}

void PlayerLevelManagement::LevelManage()
{
	if (m_exp >= 30)
	{
		m_shotattackstage = 2;
	}
	else if (m_exp >= 60)
	{
		m_shotattackstage = 3;
	}
	else if (m_exp >= 90)
	{
		m_shotattackstage = 4;
	}
}
void PlayerLevelManagement::Render(RenderContext & rc)
{
	m_fontRender.Draw(rc);
	m_fontRender2.Draw(rc);
}