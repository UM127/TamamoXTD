#include "stdafx.h"
#include "Title.h"
#include "Game.h"
//#include "sound/SoundEngine.h"
//#include "sound/SoundSource.h"

bool Title::Start()
{
	spriteRender.Init("Assets/sprite/Title.dds", 1600.0f, 900.0f);

	//g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Wanderers-City.wav");
	//g_soundEngine->ResistWaveFileBank(6, "Assets/sound/battle-start.wav");

	//titleBGM = NewGO<SoundSource>(0);
	//titleBGM->Init(0);
	////���[�v������Ƃ���true�B
	//titleBGM->Play(true);
	////���ʂ̒����B
	//titleBGM->SetVolume(0.25f);

	return true;
}

Title::Title()
{
}

Title::~Title()
{
	//DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//titleSE = NewGO<SoundSource>(0);
		//titleSE->Init(6);
		////���[�v������Ƃ���true�B
		//titleSE->Play(false);
		////���ʂ̒����B
		//titleSE->SetVolume(0.4f);

		game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);                 //�^�C�g���̕`��
}