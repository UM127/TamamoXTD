#include "stdafx.h"
#include "PlayerLevelManagement.h"
#include "Game.h"

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

	int b = m_plselectlevelup;
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"%d", b);

	//表示するテキストを設定。
	m_fontRender2.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender2.SetPosition(Vector3(400.0f, 300.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender2.SetScale(2.0f);
	//黒色に設定
	m_fontRender2.SetColor(g_vec4White);
}
void PlayerLevelManagement::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		if (m_levelUpFlag == false)
		{
			FindGO<Game>("game")->SetWorldStop(false);
		}
		else
		{
			FindGO<Game>("game")->SetWorldStop(true);
		}

		//世界が止まっていないなら
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			if (m_plselectlevelup > 4)
			{
				m_plselectlevelup = 4;
			}

			//レベル処理。
			LevelManage();
		}

		//描画処理。
		Font();
	}
}

void PlayerLevelManagement::LevelManage()
{
	if (g_pad[0]->IsTrigger(enButtonSelect))
	{
		m_levelUpFlag = true;
	}
	if (g_pad[0]->IsTrigger(enButtonB))
	{
	}
	if (m_exp >= 4)
	{
		m_shotattackstage = 5;
	}
	else if (m_exp >= 3)
	{
		m_shotattackstage = 4;
	}
	else if (m_exp >= 2)
	{
		m_shotattackstage = 3;
	}
	else if (m_exp >= 1)
	{
		m_shotattackstage = 2;
	}
}
void PlayerLevelManagement::Render(RenderContext & rc)
{
	if (FindGO<Game>("game") != NULL)
	{
		if (FindGO<Game>("game")->GetResult() == false)
		{
			m_fontRender.Draw(rc);
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}
	//m_fontRender2.Draw(rc);
}