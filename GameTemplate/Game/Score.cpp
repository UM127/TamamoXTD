#include "stdafx.h"
#include "Score.h"
#include "Result.h"
#include "Game.h"
#include "PlayerLevelManagement.h"

void Score::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		//�X�R�A��EXP������B
		m_score=FindGO<PlayerLevelManagement>("playerlevelmanagement")->GetEXP();
	}
}
