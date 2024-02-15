#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "Title.h"
#include "PlayerLevelManagement.h"
#include "EnemySpawn.h"
#include "Score.h"

bool Result::Start()
{
    //FindGO<Game>("game")->SetResult(false);
    FindGO<EnemySpawn>("enemyspawn")->ResetTimer();
    FindGO<EnemySpawn>("enemyspawn")->SetResultStop(true);
    spriteRender.Init("Assets/sprite/Result.dds", 1600.0f, 900.0f);
    spriteRender2.Init("Assets/sprite/PERFECT.dds", 1600.0f, 900.0f);

    m_resultscore = FindGO<Score>("score")->GetScore();
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
    if (g_pad[0]->IsTrigger(enButtonB) )
    {
        NewGO<Title>(0, "title");
        DeleteGO(this);
    }
    ResultUI();
}

void Result::ResultUI()
{
    int a = m_resultscore;
    wchar_t wcsbuf1[256];
    swprintf_s(wcsbuf1, 256, L"%d", a);

    //表示するテキストを設定。
    m_fontRender.SetText(wcsbuf1);
    //フォントの位置を設定。
    m_fontRender.SetPosition(Vector3(-100.0f, 30.0f, 0.0f));
    //フォントの大きさを設定。
    m_fontRender.SetScale(4.0f);
    //黒色に設定
    m_fontRender.SetColor(g_vec4Black);
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
}