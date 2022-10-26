#pragma once
class EXP;
class Player;
class PlayerLevelManagement;

class Enemy : public IGameObject
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
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	/// <summary>
	/// HP処理
	/// </summary>
	void EnemyHP();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();

private:
	ModelRender m_enemy;
	Player* m_player;
	EXP* m_exp;
	PlayerLevelManagement* m_plmanagement;
	Vector3 m_position = Vector3::Zero;				   //座標
	Vector3 m_playerposition;							//プレイヤーの座標
	Quaternion m_rotation = Quaternion::Identity;     //回転
	Vector3 m_scale = Vector3::One;	                   //拡大率
	Vector3 m_moveSpeed;							   //移動速度
	Vector3 m_forward = { 0.0f,0.0f,1.0f };                                 //キャラクターの前方向のベクトル
	CollisionObject* m_collisionObject;
	SpriteRender m_mushhpbar;							//HPバー
};

