#include "stdafx.h"
#include "Score.h"
#include "Result.h"
#include "Game.h"
#include "PlayerLevelManagement.h"

void Score::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		//スコアにEXPを入れる。
		m_score=FindGO<PlayerLevelManagement>("playerlevelmanagement")->GetEXP();
	}
}
