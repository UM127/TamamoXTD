#pragma once
class PlayerLevelManagement : public IGameObject
{
public:
	/// <summary>
	/// �J�n�̏���
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// ���x������
	/// </summary>
	void LevelManage();
	/// <summary>
	/// �����`��
	/// </summary>
	void Font();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	/// <summary>
	/// �o���l�����Z
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
	//0�Ȃ狭�����Ȃ�,1�Ȃ�e,2�Ȃ�n��,3�Ȃ琹��,4�Ȃ�u�[������
	const int& GetPlayerSelectLevelUp()
	{
		return m_plselectlevelup;
	}
	//0�Ȃ狭�����Ȃ�,1�Ȃ�e,2�Ȃ�n��,3�Ȃ琹��,4�Ȃ�u�[������
	void AddPlayerSelectLevelUp()
	{
		m_plselectlevelup++;
	}
	//0�Ȃ狭�����Ȃ�,1�Ȃ�e,2�Ȃ�n��,3�Ȃ琹��,4�Ȃ�u�[������
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
	FontRender m_fontRender;							//�t�H���g�����_�[
	FontRender m_fontRender2;							//�t�H���g�����_�[
	int m_playerweaponflag = true;		//�ŏ��̕���
	int m_playerweaponflag2 = false;
	int m_playerweaponflag3 = false;
	int m_shotattackstage = 1;
	int m_shotattackstagegun = 1;
	int m_shotattackstagelandmine = 0;
	int m_shotattackstageholywater = 0;
	int m_shotattackstageboomerang = 0;
	int m_exp=0;//�o���l
	int m_plselectlevelup = 0;
	int m_levelUpFlag = false;
};

