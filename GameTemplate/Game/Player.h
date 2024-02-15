#pragma once

class Unit;
class Attack;
class AttackManagement;
class PlayerLevelManagement;

class Player : public IGameObject
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
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();
	/// <summary>
	/// アニメーション管理関数
	/// </summary>
	void AnimationManagement();
	/// <summary>
	/// 位置の設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
public:
	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3& GetPlayerPosition()
	{
		return m_position;
	}
	/// <summary>
	/// プレイヤーの前方向のベクトル
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPlayerForward()
	{
		return m_forward;
	}
	const Quaternion& GetPlayerRot()
	{
		return m_rotation;
	}

	const Vector3& GetSideVector()
	{
		return m_side;
	}
	/// <summary>
	/// キャラクターコントローラーを取得。
	/// </summary>
	/// <returns>キャラクターコントローラー。</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimationClip_Idle,				//待機アニメーション。	
		enAnimationClip_Walk,				//歩きアニメーション。
		//enAnimationClip_Run,				//走りアニメーション。
		//enAnimationClip_Attack1,			//攻撃アニメーション。
		//enAnimationClip_Attack2,			//攻撃アニメーション。
		//enAnimationClip_Attack3,			//攻撃アニメーション。
		//enAnimationClip_MagicAttack,		//魔法攻撃アニメーション。
		//enAnimationClip_HitDamage1,			//被ダメージアニメーション。
		//enAnimationClip_HitDamage2,			//被ダメージアニメーション。
		//enAnimationClip_Down1,				//HPが0。
		//enAnimationClip_Down2,				//HPが0。
		//enAnimationClip_Down3,				//HPが0。
		//enAnimationClip_PushLever,			//レバーを押すアニメーション。
		//enAnimationClip_Winner,				//勝利アニメーション。
		enAnimationClip_Num,				//アニメーションの数。
	};

	PlayerLevelManagement* m_plmanagement;

	ModelRender m_player;                               //プレイヤー
	Animation m_animation;								// アニメーション
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;       //キャラクターコントローラー。
	Vector3 m_position= Vector3::Zero;				   //座標
	Quaternion m_rotation = Quaternion::Identity;     //回転
	Vector3 m_scale=Vector3::One;	                   //拡大率
	Vector3 m_moveSpeed;							   //移動速度
	Vector3 m_forward = {0.0f,0.0f,1.0f};                                 //キャラクターの前方向のベクトル
	Vector3 m_up = { 0.0f,1.0f,0.0f };
	Vector3 m_side=Vector3::AxisX;
	CollisionObject* m_collisionObject;

	Attack* m_attack[3];				//攻撃
	AttackManagement* m_attackmanagement;				//攻撃の管理

	int m_playerstate;
	int m_attackstate = false;			//攻撃可能か不可能か
	int m_hp = 1;
	float m_attackmadetimer[5];
	float m_attackcooltime[5];
	float m_timer = 0.0f;
};