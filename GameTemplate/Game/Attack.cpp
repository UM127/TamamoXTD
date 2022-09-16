#include "stdafx.h"
#include "Attack.h"
#include "Player.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"
//EffectEmitterを使用する時はファイルをインクルードする必要がある。
#include "graphics/effect/EffectEmitter.h"

bool Attack::Start()
{
	//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
	m_position = FindGO<Player>("player")->GetPlayerPosition();
	m_position.y += 70.0f;
	m_playerposition = FindGO<Player>("player")->GetPlayerPosition();

		//弾のモデルを読み込む。
		m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm");
		m_modelRender.SetScale({ 0.2f,0.2f,0.2f });
		//FindGOで読み込んで入れたm_positionに弾を配置する。
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		//コライダーを初期化。
		m_sphereCollider.Create(48.0f);

		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//座標を敵の位置に設定する。
		collisionPosition = m_position;
		//球状のコリジョンを作成する。
		m_collisionObject->CreateSphere(collisionPosition,       //座標。
			Quaternion::Identity,                                   //回転。
			30.0f);                                                //球の大きさ(半径)。
			//名前を付ける。
		m_collisionObject->SetName("SoysauceAttack");
		//自動で削除を無効にする(DeleteGOで削除する必要がある)。
		m_collisionObject->SetIsEnableAutoDelete(false);
	
	return true;
}

Attack::Attack()
{

}

Attack::~Attack()
{
	DeleteGO(m_collisionObject);
}

void Attack::Update() //常に1秒間に60回呼び出される
{
	Move();
	//更新処理。
	m_modelRender.Update();
}

void Attack::Move()
{
	//弾の座標にmovespeedを+してやって、弾を動かす。
	m_position += m_moveSpeed * 15.0f;
	m_modelRender.SetPosition(m_position);
	//setpositionで動いた弾の当たり判定の反映
	m_collisionObject->SetPosition(m_position);
	//プレイヤーの座標と弾の距離のベクトルを求める。
	Vector3 diff = m_playerposition - m_position;

	//生成されてから5秒経過したら
	if (m_deletetimer >= 5.0f)
	{
		DeleteGO(this);
	}
	m_deletetimer += g_gameTime->GetFrameDeltaTime();

}

void Attack::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}