#include "stdafx.h"
#include "Attack.h"
#include "Player.h"
#include "Game.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"
//EffectEmitterを使用する時はファイルをインクルードする必要がある。
#include "graphics/effect/EffectEmitter.h"
//乱数を使えるようにする
#include <random>

namespace
{
	//乱数を生成
	constexpr int MIN = -600;//乱数の範囲最低値
	constexpr int MAX = 600;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数
}

bool Attack::Start()
{
	//弾
	if (m_attackno == 0)
	{
		m_player = FindGO<Player>("player");
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = m_player->GetPlayerPosition();
			//if (m_attackA == 0)
			//{
			//	m_position += m_side*20.0f;
			//}
			//if (m_attackA == 1)
			//{
			//	m_position -= m_side * 20.0f;
			//}
		m_position.y += 40.0f;
		m_position += m_moveSpeed * 10.0f;
		m_playerposition = m_player->GetPlayerPosition();
		//弾のモデルを読み込む。
		m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm",true,true);
		m_modelRender.SetScale({ 0.2f,0.2f,0.2f });
		//FindGOで読み込んで入れたm_positionに弾を配置する。
		m_modelRender.SetPosition(m_position);
		m_modelRender.Update();
		//コライダーを初期化する。
		m_sphereCollider.Create(48.0f);

		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//座標を敵の位置に設定する。
		collisionPosition = m_position;
		//Box状のコリジョンを作成する。
		m_collisionObject->CreateBox(collisionPosition,       //座標。
			m_player->GetPlayerRot(),                                 //回転。
			{ 40.0f,20.0f,20.0f });                                                //Boxの大きさ。
			//名前を付ける。
		m_collisionObject->SetName("BulletAttack");
		//自動で削除を無効にする(DeleteGOで削除する必要がある)。
		m_collisionObject->SetIsEnableAutoDelete(false);
	}
	//聖水
	else if (m_attackno == 1)
	{
		m_player = FindGO<Player>("player");
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = m_player->GetPlayerPosition();
		m_position.y = 500.0f;
		//敵の乱数。
		std::random_device rd;
		std::default_random_engine eng(rd());
		std::uniform_int_distribution<int> distr(MIN, MAX);
		int holypos = 0;
		for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
			switch (holypos) {
			case 0:
				m_position.x = m_position.x + distr(eng);
				holypos++;
				break;
			case 1:
				m_position.z = m_position.z + distr(eng);
				break;
			}
		}
		//モデルの読み込み
		m_modelRender.Init("Assets/modelData/holywater.tkm", true, false);
		//m_rotation.AddRotationDegY(180.0f);
		m_modelRender.SetScale({ 3.0f,3.0f,3.0f });
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
		m_collisionObject->CreateBox(collisionPosition,       //座標。
			Quaternion::Identity,                                   //回転。
			{ 100.0f,8.0f,100.0f});                                                //球の大きさ(半径)。
			//"BulletAttack"は仮名、聖水。
		m_collisionObject->SetName("BulletAttack");
		//自動で削除を無効にする(DeleteGOで削除する必要がある)。
		m_collisionObject->SetIsEnableAutoDelete(false);
		return true;

	}
	//地雷
	else if (m_attackno == 2)
	{
		m_player = FindGO<Player>("player");
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = m_player->GetPlayerPosition();
		m_position.y = 5.0f;
		m_position -= m_moveSpeed * 30.0f;
		//モデルの読み込み
		m_modelRender.Init("Assets/modelData/mine.tkm", true, false);
		m_rotation.SetRotationDegY(50.0f);
		m_modelRender.SetScale({ 2.0f,2.0f,2.0f });
		//FindGOで読み込んで入れたm_positionに弾を配置する。
		m_modelRender.SetPosition(m_position);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.Update();
		//コライダーを初期化。
		m_sphereCollider.Create(48.0f);

		//コリジョンオブジェクトを作成する。
		m_collisionObject = NewGO<CollisionObject>(0);
		Vector3 collisionPosition = m_position;
		//座標を敵の位置に設定する。
		collisionPosition = m_position;
		//球状のコリジョンを作成する。
		m_collisionObject->CreateBox(collisionPosition,       //座標。
			Quaternion::Identity,                                   //回転。
			{ 100.0f,8.0f,100.0f });                                                //球の大きさ(半径)。
			//"BulletAttack"は仮名、地雷。
		m_collisionObject->SetName("BulletAttack");
		//自動で削除を無効にする(DeleteGOで削除する必要がある)。
		m_collisionObject->SetIsEnableAutoDelete(false);
		return true;

	}
	//ブーメラン
	else if (m_attackno == 3)
	{
		m_player = FindGO<Player>("player");
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = m_player->GetPlayerPosition();
		m_position.y += 40.0f;
		m_position += m_moveSpeed * 10.0f;
		m_playerposition = m_player->GetPlayerPosition();
		//弾のモデルを読み込む。
		m_modelRender.Init("Assets/modelData/boomerang.tkm", false, false);
		m_modelRender.SetScale({ 2.0f,1.0f,2.0f });
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
		//Box状のコリジョンを作成する。
		m_collisionObject->CreateBox(collisionPosition,       //座標。
			m_player->GetPlayerRot(),                                   //回転。
			{ 60.0f,30.0f,30.0f });                                                //Boxの大きさ。
			//名前を付ける。
		m_collisionObject->SetName("BulletAttack");
		//自動で削除を無効にする(DeleteGOで削除する必要がある)。
		m_collisionObject->SetIsEnableAutoDelete(false);
	}
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
	if (FindGO<Game>("game") != NULL)
	{
		//世界が止まっていないなら
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			//骨攻撃で、タイマーが4.9秒以内なら
			if (m_attackno == 3 && m_deletetimer <= 4.9f)
			{
				//ヒット判定用のコリジョンの配列を取得。
				const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_hit");

				//for文で配列を回す。
				for (auto collision : collisions)
				{
					//弾のコリジョンと敵のコリジョンが。
					//衝突していて、バウンド回数が4回以下なら。
					if (collision->IsHit(m_collisionObject) == true && m_bounce <= 3)
					{
						m_bounce++;
						m_deletetimer = 0.0f;
					}
				}
			}
			Move();
			//更新処理。
			m_modelRender.Update();
		}
	}
}

void Attack::Move()
{
	if (m_attackno == 0)
	{
		//弾の座標にmovespeedを+してやって、弾を動かす。
		m_position += m_moveSpeed * 10.0f;
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
	if (m_attackno == 1)
	{
		m_position.y -= 5.0f;

		if (m_position.y <= 5.0f)
		{
			m_position.y = 5.0f;
		}
		m_modelRender.SetPosition(m_position);
		m_collisionObject->SetPosition(m_position);
		m_modelRender.Update();
		//生成されてから5秒経過したら
		if (m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackno == 2)
	{

		//生成されてから5秒経過したら
		if (m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_attackno ==3)
	{
		//跳ねた数が0,2なら弾の座標にmovespeedを+してやって、弾を動かす。
		if (m_bounce == 0 || m_bounce == 2)
		{
			m_position += m_moveSpeed * 15.0f;
		}
		//跳ねた数が1,3なら弾の座標にmovespeedを-してやって、弾を動かす。
		if (m_bounce == 1 || m_bounce >= 3)
		{
			m_position -= m_moveSpeed * 15.0f;
		}
		m_rotation.AddRotationY(50.0f);
		m_modelRender.SetRotation(m_rotation);
		m_modelRender.SetPosition(m_position);
		//setpositionで動いた弾の当たり判定の反映
		m_collisionObject->SetPosition(m_position);
		m_collisionObject->SetRotation(m_rotation);
		//プレイヤーの座標と弾の距離のベクトルを求める。
		Vector3 diff = m_playerposition - m_position;

		//5秒経過しているか、バウンド数が3回以上なら
		if (m_bounce >= 4|| m_deletetimer >= 5.0f)
		{
			DeleteGO(this);
		}
		m_deletetimer += g_gameTime->GetFrameDeltaTime();
	}
}

void Attack::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}