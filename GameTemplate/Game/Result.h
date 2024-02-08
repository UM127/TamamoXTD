#pragma once
class Result
{
public:
    Result();
    ~Result();

    bool Start();
    void ResultUI();
    void Update();
    void Render(RenderContext& rc);

    /// <summary>
    /// クリアしているか
    /// </summary>
    /// <param name="clear"></param>
    void SetClear()
    {
        m_GameClear = true;
    }

    /// <summary>
    ///クリアしたかを取得する。
    /// </summary>
    /// <returns>プレイヤーの座標。</returns>
    const int& GetClear() const
    {
        return m_GameClear;
    }

private:
    int m_GameClear = false;          // ゲームクリアか否か
    SoundSource* resultBGM;                          //タイトルBGM
    SpriteRender spriteRender; //スプライトレンダ―。
    SpriteRender spriteRender2;
    SoundSource* clearBGM;      //clearBGMを読み込む
    FontRender m_fontRender;  //文字の表示
    FontRender m_fontRender2;  //文字の表示
};

