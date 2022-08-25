#pragma once

class Unit;

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
	/// 文字描画
	/// </summary>
	void Font();
	/// <summary>
	/// 召喚用のボックスの移動処理
	/// </summary>
	void SummonBoxMove()
	{
		//召喚用のボックスを常にプレイヤーの前にあるようにする。
		m_summonboxpos = m_position;
		m_summonboxpos += m_forward*70.0f;
		m_summonboxcollisionObject = m_summonboxpos;

		m_summonbox.SetPosition(m_summonboxpos);
		m_summonbox.Update();
		m_collisionObject->SetPosition(m_summonboxcollisionObject);
		m_collisionObject->Update();
	}
	/// <summary>
	/// ユニット選択関数
	/// </summary>
	void SelectUnittype()
	{
		//選択されてるユニットが０以外でLB1が押されたとき番号を-1する
		if (m_summonUnitNo != 0 && g_pad[0]->IsTrigger(enButtonLB1))
		{
			m_summonUnitNo--;
		}
		//選択されてるユニットが上限未満でRB1が押されたとき番号を+1する
		if (m_summonUnitNo<m_UnitMaxnum&& g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_summonUnitNo++;
		}
	}

public:
	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3& GetPlayerPosition() const
	{
		return m_position;
	}



private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimationClip_Idle,				//待機アニメーション。	
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

	Unit* m_unit = nullptr;

	ModelRender m_player;                               //プレイヤー
	ModelRender m_summonbox;							//召喚用のボックス
	FontRender m_fontRender;							//フォントレンダー
	FontRender m_fontRender3;							//フォントレンダー
	Animation m_animation;								// アニメーション
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;       //キャラクターコントローラー。
	Vector3 m_position= Vector3::Zero;				   //座標
	Quaternion m_rotation = Quaternion::Identity;     //回転
	Vector3 m_scale=Vector3::One;	                   //拡大率
	Vector3 m_moveSpeed;							   //移動速度
	Vector3 m_summonboxpos = Vector3::Zero;					//召喚用のボックスの位置
	Vector3 m_summonboxcollisionObject = Vector3::Zero;		//召喚用のボックスのコリジョンの位置
	Vector3 m_forward;                                 //キャラクターの前方向のベクトル
	CollisionObject* m_collisionObject;

	int m_UnitMaxnum = 2;//ユニット番号の最大値
	int m_summonUnitNo = 0;
	int m_playerState;
	float m_timer = 0.0f;
};