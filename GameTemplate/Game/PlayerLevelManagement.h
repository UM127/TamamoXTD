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
	FontRender m_fontRender;							//�t�H���g�����_�[
	FontRender m_fontRender2;
	int m_playerweaponflag = true;		//�ŏ��̕���
	int m_playerweaponflag2 = false;
	int m_playerweaponflag3 = false;
	int m_shotattackstage = 1;
	int m_exp=0;//�o���l
};

