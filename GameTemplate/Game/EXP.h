#pragma once
class Player;
class PlayerLevelManagement;

class EXP : public IGameObject
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
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();
	void EXPProcess();
	/// <summary>
	/// 位置の設定
	/// </summary>
	/// <param name="exppos"></param>
	void SetEXPPos(const Vector3& exppos)
	{
		m_exposition = exppos;
	}

private:
	Player* m_player;									//プレイヤー
	PlayerLevelManagement* m_plmanagement;
	ModelRender m_exp;
	Vector3 m_exposition = Vector3::Zero;			   //座標
	Quaternion m_exrotation = Quaternion::Identity;    //回転
	Vector3 m_scale = Vector3::One;	                   //拡大率
	Vector3 m_forward = { 0.0f,0.0f,1.0f };            //キャラクターの前方向のベクトル
	CollisionObject* m_collisionObject;
};

