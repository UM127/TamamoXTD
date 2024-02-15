#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Attack.h"
#include "Attackmanagement.h"
#include "PlayerLevelManagement.h"
//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

namespace
{
	const int PL_MOVESPEED = 150.0f;
}

bool Player::Start()
{
	m_plmanagement = NewGO<PlayerLevelManagement>(0, "playerlevelmanagement");
	m_attackmanagement = NewGO<AttackManagement>(0, "attackmanagement");
	//アニメーションを読み込む
	m_animationClipArray[enAnimationClip_Idle].Load("Assets/animData/Vanguard/Idle.tka");
	m_animationClipArray[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimationClip_Walk].Load("Assets/animData/Vanguard/Walk.tka");
	m_animationClipArray[enAnimationClip_Walk].SetLoopFlag(true);
	//モデルの読み込み
	m_player.Init("Assets/modelData/model/Vanguard/Vanguard.tkm", false,false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの位置に設定する。
	collisionPosition = m_position;
	//collisionPosition.y = 50.0f;
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(collisionPosition,       //座標。
		Quaternion::Identity,                             //回転。
		15.0f);                                          //球の大きさ(半径)。
	//名前を付ける。
	m_collisionObject->SetName("player_hit");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	//キャラコンを初期化する。
	m_characterController.Init(15.0f, 40.0f, m_position);
	m_player.SetRotation(m_rotation);
	m_player.SetPosition(m_position);
	m_player.Update();

	return true;
}

void Player::Update()
{
	//世界が止まっていないなら
	if (FindGO<Game>("game") != NULL)
	{
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			//描画処理。
			Font();

			//移動処理。
			Move();
			//回転処理。
			Rotation();
			//アニメーション管理
			AnimationManagement();
			/*
			m_player.UpdateWorldMatrix(
				m_characterController.GetPosition(),
				m_rotation,
				g_vec3One
			);
			*/
			m_player.Update();
		}
		//ヒット判定用のコリジョンの配列を取得。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_hit");

		//for文で配列を回す。
		for (auto collision : collisions)
		{
			//敵のコリジョンとプレイヤーのコリジョンが。
			//衝突していたらゲームオーバーにする。
			if (collision->IsHit(m_collisionObject) == true)
			{
				DeleteGO(m_collisionObject);
				FindGO<Game>("game")->SetResult(true);
			}
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}

}
void Player::AnimationManagement()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_playerstate = 1;
	}
	else
	{
		m_playerstate = 0;
	}
	if (m_playerstate == 0)
	{
		m_player.PlayAnimation(enAnimationClip_Idle, 0.2f);
	}
	if (m_playerstate == 1)
	{
		m_player.PlayAnimation(enAnimationClip_Walk, 0.2f);
	}
}
void Player::Move()
{
	//移動速度を初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//このフレームの移動量を求める。
	//左スティックの入力量を受け取る。
	m_position.x = g_pad[0]->GetLStickXF();
	m_position.y = g_pad[0]->GetLStickYF();
	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed += cameraForward * m_position.y * PL_MOVESPEED;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * m_position.x * PL_MOVESPEED;		//右方向への移動速度を加算。

	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	m_collisionObject->SetPosition(m_position);

	m_player.SetPosition(m_position);
	m_player.Update();
}

void Player::Rotation()
{
		//xかzの移動速度があったら(スティックの入力があったら)。
		if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		{
			if (!g_pad[0]->IsPress(enButtonA))
			{
				float rot = atan2(-m_moveSpeed.x, m_moveSpeed.z);
				//キャラクターの方向を変える。
				m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
				//回転。
				m_player.SetRotation(m_rotation);
			}
			//プレイヤーの前方向のベクトルを設定する。
			m_forward = Vector3::AxisZ;
			m_up = Vector3::AxisY;
			//ベクトルにクウォータニオンを適応してプレイヤーの向きに回転させる
			m_rotation.Apply(m_forward);
			m_side.Cross(m_up, m_forward);



		}
}

void Player::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}