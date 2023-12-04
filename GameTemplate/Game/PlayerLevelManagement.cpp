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
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(400.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
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
	if (m_exp >= 5)
	{
		m_shotattackstage = 5;
	}
	else if (m_exp >= 4)
	{
		m_shotattackstage = 4;
	}
	else if (m_exp >= 3)
	{
		m_shotattackstage = 3;
	}
	else if (m_exp >= 2)
	{
		m_shotattackstage = 2;
	}
}
void PlayerLevelManagement::Render(RenderContext & rc)
{
	m_fontRender.Draw(rc);
}