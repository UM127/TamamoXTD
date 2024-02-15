#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "Title.h"
#include "PlayerLevelManagement.h"
#include "EnemySpawn.h"
#include "Score.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

bool Result::Start()
{
    FindGO<EnemySpawn>("enemyspawn")->ResetTimer();
    FindGO<EnemySpawn>("enemyspawn")->SetResultStop(true);
    spriteRender.Init("Assets/sprite/Result.dds", 1600.0f, 900.0f);
    spriteRender2.Init("Assets/sprite/PERFECT.dds", 1600.0f, 900.0f);

    m_resultscore = FindGO<Score>("score")->GetScore();
    g_soundEngine->ResistWaveFileBank(3, "Assets/sound/kettei.wav");

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
    //A�{�^���������ꂽ��Title��NewGO����B
    if (g_pad[0]->IsTrigger(enButtonB) )
    {
        ResultSE = NewGO<SoundSource>(0);
        ResultSE->Init(3);
        //���[�v������Ƃ���true�B
        ResultSE->Play(false);
        //���ʂ̒����B
        ResultSE->SetVolume(0.7f);

        DeleteGO(this);
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

    //�\������e�L�X�g��ݒ�B
    m_fontRender.SetText(wcsbuf1);
    //�t�H���g�̈ʒu��ݒ�B
    m_fontRender.SetPosition(Vector3(-100.0f, 30.0f, 0.0f));
    //�t�H���g�̑傫����ݒ�B
    m_fontRender.SetScale(4.0f);
    //���F�ɐݒ�
    m_fontRender.SetColor(g_vec4Black);
}

void Result::Render(RenderContext& rc)
{
        //�摜��`�悷��B
        spriteRender.Draw(rc);
        if (m_GameClear == true)
        {
            spriteRender2.Draw(rc);
        }
        //�t�H���g��`�悷��B
        m_fontRender.Draw(rc);
}