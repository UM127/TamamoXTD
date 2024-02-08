#include "stdafx.h"
#include "Result.h"
#include "Game.h"
//#include "Title.h"
#include "PlayerLevelManagement.h"

bool Result::Start()
{
    FindGO<Game>("game")->SetResult(false);

    spriteRender.Init("Assets/sprite/Result.dds", 1920.0f, 1080.0f);
    spriteRender2.Init("Assets/sprite/PERFECT.dds", 1920.0f, 1080.0f);
    //g_soundEngine->ResistWaveFileBank(4, "Assets/sound/Crasher.wav");

    //resultBGM = NewGO<SoundSource>(0);
    //resultBGM->Init(4);
    ////ループさせるときはtrue。
    //resultBGM->Play(true);
    ////音量の調整。
    //resultBGM->SetVolume(0.25f);
    return true;

}

Result::Result()
{
}

Result::~Result()
{
    //DeleteGO(resultBGM);
}

void Result::Update()
{
    //Aボタンを押されたらTitleをNewGOする。
    if (g_pad[0]->IsTrigger(enButtonA) )
    {
        //NewGO<Title>(0, "title");
        //DeleteGO(this);
    }
    ResultUI();
}

void Result::ResultUI()
{
}

void Result::Render(RenderContext& rc)
{
        //画像を描画する。
        spriteRender.Draw(rc);
        if (m_GameClear == true)
        {
            spriteRender2.Draw(rc);
        }
        //フォントを描画する。
        m_fontRender.Draw(rc);
        m_fontRender2.Draw(rc);
}