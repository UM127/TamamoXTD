#pragma once

class Player;

class Attack : public IGameObject
{
public:
	Attack();
	~Attack();
	//最初に一回だけ実行
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//移動速度の設定
	void SetMoveSpeed(const Vector3& sms)
	{
		m_moveSpeed = sms;
	}
	/// <summary>
	/// 攻撃の種類の設定
	/// </summary>
	/// <param name="attack"></param>
	void SetAttack(const int&attack)
	{
		m_attackno=attack;
	}
	/// <summary>
	/// 攻撃の座標の設定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	///座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3& GetAttackPosition() const
	{
		return m_position;
	}

private:
	FontRender m_fontRender;                     //文字の描画
	SphereCollider m_sphereCollider;		    //円型のコライダー。
	Vector3 m_playerposition;                  //プレイヤーの位置
	Vector3 m_enemyposition;                  //敵の位置
	Vector3 m_position;			              //座標。
	Vector3 m_moveSpeed;					 //移動速度。
	Vector3   m_bulletposition;             //弾の位置
	Vector3	m_efpos1;						//エフェクト用のポジション
	Quaternion m_rotation;                  //クウォータニオン
	ModelRender m_modelRender;             //モデルレンダー
	Player* m_player;
	CollisionObject* m_collisionObject;
	float m_deletetimer = 0.0f;
	int bulletdelete = 0;
	int m_attackno = 0;
};

