#pragma once
class PlayerLevelManagement;

class GameUI : public IGameObject
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
	/// ��~���̏���
	/// </summary>
	void Pause();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
private:
	SpriteRender m_playericon;
	SpriteRender m_pistolsprite;
	SpriteRender m_holywater;
	SpriteRender m_mine;
	SpriteRender m_boomerang;
	SpriteRender m_levelup;
	SpriteRender m_cursor;
	SpriteRender m_pistolstarsprite[5];
	SpriteRender m_holystarsprite[5];
	SpriteRender m_minestarsprite[5];
	SpriteRender m_boomerangstarsprite[5];
	PlayerLevelManagement* m_plmanager;
};

