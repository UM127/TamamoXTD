#pragma once
#include "sound/SoundSource.h"

class Game;
class Title;

class Result : public IGameObject
{
public:
    Result();
    ~Result();

    bool Start();
    void ResultUI();
    void Update();
    void Render(RenderContext& rc);

    /// <summary>
    /// �N���A���Ă��邩
    /// </summary>
    /// <param name="clear"></param>
    void SetClear()
    {
        m_GameClear = true;
    }

    /// <summary>
    ///�N���A���������擾����B
    /// </summary>
    /// <returns>�v���C���[�̍��W�B</returns>
    const int& GetClear() const
    {
        return m_GameClear;
    }
    const int& GetResultStop() const
    {
        return m_resultstop;
    }


private:
    int m_GameClear = false;          // �Q�[���N���A���ۂ�
    int m_resultstop = false;
    int m_resultscore = 0;
    SoundSource* ResultSE;                          //���U���gSE
    SpriteRender spriteRender; //�X�v���C�g�����_�\�B
    SpriteRender spriteRender2;
    SoundSource* clearBGM;      //clearBGM��ǂݍ���
    FontRender m_fontRender;  //�����̕\��
    FontRender m_fontRender2;  //�����̕\��
};

