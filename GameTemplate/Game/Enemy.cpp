#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "EXP.h"
#include "Attack.h"
#include "Game.h"
#include "EnemySpawn.h"
//乱数を使えるようにする
#include <random>
//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

namespace
{
	//乱数を生成
	constexpr int MIN = -800;//乱数の範囲最低値
	constexpr int MAX = 800;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数
	//const int E_MUSH_MAXHP = 10;//青キノコの最大HP
	const int MUSHMOVESPEED = 1.95f;//キノコの移動速度
}

bool Enemy::Start()
{
	m_player = FindGO<Player>("player");
	//敵の乱数。
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	int enepos = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (enepos) {
		case 0:
			m_position.x = m_player->GetPlayerPosition().x + distr(eng);
			enepos++;
			break;
		case 1:
			m_position.z = m_player->GetPlayerPosition().z + distr(eng);
			break;
		}
	}

	if (0.0f < m_player->GetPlayerPosition().x + m_position.x)
	{
		m_position.x += 100.0f;
	}
	else if (m_player->GetPlayerPosition().x + m_position.x <= 0.0f)
	{
		m_position.x -= 100.0f;
	}

	if (0.0f < m_player->GetPlayerPosition().z + m_position.z)
	{
		m_position.z += 100.0f;
	}
	else if (m_player->GetPlayerPosition().z + m_position.z <= 0.0f)
	{
		m_position.z -= 100.0f;
	}

	//モデルの読み込み
	m_enemy.Init("Assets/modelData/model/mush/bluemush.tkm", false);

	//初期化。
	m_enemy.SetScale(0.3f, 0.3f, 0.3f);
	m_enemy.SetRotation(m_rotation);
	m_enemy.SetPosition(m_position);
	m_enemy.Update();

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//Box状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_position,       //座標。
		Quaternion::Identity,                                   //回転。
		{ 40.0f,40.0f,40.0f });                                                //Boxの大きさ。
	//名前を付ける。
	m_collisionObject->SetName("enemy_hit");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	//EnemyHP();

	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 3)
	{
		m_hp = 20;
	}
	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 2)
	{
		m_hp = 10;
	}
	if (FindGO<EnemySpawn>("enemyspawn")->GetEnemyLevel() == 1)
	{
		m_hp = 1;
	}

	return true;
}
void Enemy::Update()
{
	if (FindGO<Game>("game") != NULL)
	{
		if (m_hp <= 0)
		{
			m_exp = NewGO<EXP>(0, "exp");
			m_exp->SetEXPPos(m_position);
			//m_plmanagement->AddEXP();
			DeleteGO(m_collisionObject);
			DeleteGO(this);
		}
		//世界が止まっていないなら
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			m_attack = FindGO<Attack>("attack");
			Move();
			Rotation();
			//モデルの更新処理。
			m_enemy.Update();
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(m_collisionObject);
		DeleteGO(this);
	}
}

void Enemy::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotationY(-angle);

	//回転を設定する。
	m_enemy.SetRotation(m_rotation);

	//プレイヤーの前ベクトルを計算する。
	m_forward = Vector3::AxisZ;
	m_rotation.Apply(m_forward);
}

void Enemy::Move()
{
	m_playerposition = m_player->GetPlayerPosition();
	//エネミーを移動させる。
	Vector3 diff = m_playerposition - m_position;
	diff.Normalize();
	//速度いじれる
	m_moveSpeed = diff * MUSHMOVESPEED;
	m_position += m_moveSpeed;

	//座標を設定する。
	m_enemy.SetPosition(m_position);

	//ヒット判定用のコリジョンの配列を取得。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("BulletAttack");

	//for文で配列を回す。
	for (auto collision : collisions)
	{
		//弾のコリジョンと敵のコリジョンが。
		//衝突していたら。
		if (collision->IsHit(m_collisionObject) == true)
		{
			m_hp--;
		}
	}

	Vector3 m_collisionPosition = m_position;
	m_collisionPosition.y = 20.0f;
	//setpositionで動いた敵の当たり判定の反映
	m_collisionObject->SetPosition(m_collisionPosition);
}
void Enemy::EnemyHP()
{
	m_mushhpbar.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);
	m_mushhpbar.SetPosition(Vector3(-660.0f, -363.0f, 0.0f));
}
void Enemy::Render(RenderContext& rc)
{
	//m_mushhpbar.Draw(rc);
	m_enemy.Draw(rc);
}