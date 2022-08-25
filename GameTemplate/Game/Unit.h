#pragma once
class Player;

class Unit : public IGameObject
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

public:
	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3& GeUnitPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ユニットタイプの指定
	/// </summary>
	/// <param name="no"></param>
	void SetUnitTipe(const int no)
	{
		m_characterNo = no;
	}
	/// <summary>
	/// ユニットタイプの取得
	/// </summary>
	/// <returns></returns>
	const int GetUnitTipe()const
	{
		return m_characterNo;
	}
	void SetFirstsetup(const int setup)
	{
		m_SetUp=setup;
	}
	void SetPosition(Vector3 sp)
	{
		m_position = sp;
	}
private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimationClip_Punch,				//待機アニメーション。	
		//enAnimationClip_Walk,				//歩きアニメーション。
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


	Model m_model;
	ModelRender m_unit;                               //ユニット
	ModelRender m_attackcircle;							//攻撃範囲
	Player* m_player;									//プレイヤー
	Animation m_animation;								// アニメーション
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;       //キャラクターコントローラー。
	Vector3 m_position = Vector3::Zero;				   // 座標
	Quaternion m_rotation = Quaternion::Identity;;     // 回転
	Vector3 m_scale = Vector3::One;	                   // 拡大率
	CollisionObject* m_collisionObject;

	int m_playerState;
	int m_characterNo=0;
	float m_timer = 0.0f;
	//初回で軽くするために出して消す
	int m_SetUp = false;
};