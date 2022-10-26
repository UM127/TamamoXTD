#pragma once
class PlayerLevelManagement : public IGameObject
{
public:
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// レベル処理
	/// </summary>
	void LevelManage();
	/// <summary>
	/// 文字描画
	/// </summary>
	void Font();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	void AddEXP()
	{
		m_exp++;
	}
	const int& GetWeaponFlag()
	{
		return m_playerweaponflag;
	}
	const int& GetWeaponFlag2()
	{
		return m_playerweaponflag2;
	}
	const int& GetWeaponFlag3()
	{
		return m_playerweaponflag3;
	}
	const int& GetShotStage()
	{
		return m_shotattackstage;
	}
private:
	FontRender m_fontRender;							//フォントレンダー
	FontRender m_fontRender2;
	int m_playerweaponflag = true;		//最初の武器
	int m_playerweaponflag2 = false;
	int m_playerweaponflag3 = false;
	int m_shotattackstage = 1;
	int m_exp=0;//経験値
};

