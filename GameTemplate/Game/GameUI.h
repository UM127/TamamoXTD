#pragma once
class PlayerLevelManagement;

class GameUI : public IGameObject
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
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
private:
	SpriteRender m_playericon;
	SpriteRender m_pistolsprite;
	SpriteRender m_holywater;
	SpriteRender m_pistolstarsprite[5];
	SpriteRender m_holystarsprite[5];
	PlayerLevelManagement* m_plmanager;
};

