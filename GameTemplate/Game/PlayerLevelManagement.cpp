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

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(400.0f, 500.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	//���F�ɐݒ�
	m_fontRender.SetColor(g_vec4White);
}
void PlayerLevelManagement::Update()
{
	//�`�揈���B
	Font();

	//���x�������B
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