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
	/// <summary>
	/// 経験値を加算
	/// </summary>
	void AddEXP()
	{
		m_exp++;
	}
	const int& GetEXP()
	{
		return m_exp;
	}
	void DownEXP(const int& exp)
	{
		m_exp -= exp;
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
	const int& GetShotStageGun()
	{
		return m_shotattackstagegun;
	}
	const int& GetShotStageLandMine()
	{
		return m_shotattackstagelandmine;
	}
	const int& GetShotStageHolyWater()
	{
		return m_shotattackstageholywater;
	}
	const int& GetShotStageBoomerang()
	{
		return m_shotattackstageboomerang;
	}

	void AddShotStageGun()
	{
		m_shotattackstagegun++;
	}
	void AddShotStageLandMine()
	{
		m_shotattackstagelandmine++;
	}
	void AddShotStageHolyWater()
	{
		m_shotattackstageholywater++;
	}
	void AddShotStageBoomerang()
	{
		m_shotattackstageboomerang++;
	}
	//0なら強化しない,1なら銃,2なら地雷,3なら聖水,4ならブーメラン
	const int& GetPlayerSelectLevelUp()
	{
		return m_plselectlevelup;
	}
	//0なら強化しない,1なら銃,2なら地雷,3なら聖水,4ならブーメラン
	void AddPlayerSelectLevelUp()
	{
		m_plselectlevelup++;
	}
	//0なら強化しない,1なら銃,2なら地雷,3なら聖水,4ならブーメラン
	void DownPlayerSelectLevelUp()
	{
		m_plselectlevelup--;
	}
	void SetPlayerSelectLevelUp(const int& plsec)
	{
		m_plselectlevelup = plsec;
	}

	const int& GetLevelUpFlag()
	{
		return m_levelUpFlag;
	}
	void SetLevelUpFlag(const int& setflag)
	{
		m_levelUpFlag = setflag;
	}
private:
	FontRender m_fontRender;							//フォントレンダー
	FontRender m_fontRender2;							//フォントレンダー
	int m_playerweaponflag = true;		//最初の武器
	int m_playerweaponflag2 = false;
	int m_playerweaponflag3 = false;
	int m_shotattackstage = 1;
	int m_shotattackstagegun = 1;
	int m_shotattackstagelandmine = 0;
	int m_shotattackstageholywater = 0;
	int m_shotattackstageboomerang = 0;
	int m_exp=0;//経験値
	int m_plselectlevelup = 0;
	int m_levelUpFlag = false;
};

