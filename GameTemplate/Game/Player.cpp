#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"
#include "Unit.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

bool Player::Start()
{
	//アニメーションを読み込む
	m_animationClipArray[enAnimationClip_Idle].Load("Assets/animData/nonPBR/Idle.tka");
	m_animationClipArray[enAnimationClip_Idle].SetLoopFlag(true);
	//モデルの読み込み
	m_player.Init("Assets/modelData/model/PBR/nonPBR.tkm", m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	m_summonbox.Init("Assets/modelData/summonbox.tkm");
	m_summonbox.SetScale({7.5f,1.0f,7.5f});
	m_summonbox.Update();
	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//OX状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_summonboxcollisionObject,       //座標。
		Quaternion::Identity,                                   //回転。
		{ 75.0f,1.0f,75.0f });                                                //球の大きさ(半径)。
		//名前を付ける。
	m_collisionObject->SetName("summonbox");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);
	
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_player.SetRotation(m_rotation);
	m_player.SetPosition(m_position);
	m_player.Update();

	return true;
}

void Player::Update()
{
	//描画処理。
	Font();

	//移動処理。
	Move();
	//回転処理。
	Rotation();

	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/

	SummonBoxMove();
	m_player.Update();
}

void Player::Font()
{
	wchar_t wcsbuf1[256];
	int unittype = m_summonUnitNo;
	if (unittype == 0)
	{
		swprintf_s(wcsbuf1, 256, L"Vangard");
	}
	else if (unittype == 1)
	{
		swprintf_s(wcsbuf1, 256, L"ArmStrong");
	}
	else if (unittype == 2)
	{
		swprintf_s(wcsbuf1, 256, L"Magic");
	}
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(400.0f, 520.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.5f);
	//白色に設定
	m_fontRender.SetColor(g_vec4White);
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
	m_moveSpeed += cameraForward * m_position.y * 50.0f;	//奥方向への移動速度を加算。
	m_moveSpeed += cameraRight * m_position.x * 50.0f;		//右方向への移動速度を加算。

	//キャラクターコントローラーを使用して、座標を更新。
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (g_pad[0]->IsTrigger(enButtonB))
	{
			m_unit = NewGO<Unit>(0, "unit");
			//ユニットタイプのものを召喚する。
			m_unit->SetUnitTipe(m_summonUnitNo);
			m_unit->SetPosition(m_summonboxpos);
	}
	SelectUnittype();

	m_player.SetPosition(m_position);
	m_player.Update();
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		float rot = atan2(-m_moveSpeed.x, m_moveSpeed.z);
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//回転。
		m_player.SetRotation(m_rotation);
		//プレイヤーの前方向のベクトルを設定する。
		m_forward = Vector3::AxisZ;
		//ベクトルにクウォータニオンを適応してプレイヤーの向きに回転させる
		m_rotation.Apply(m_forward);
	}
}

void Player::Render(RenderContext& rc)
{
	m_player.Draw(rc);
	m_summonbox.Draw(rc);
	m_fontRender.Draw(rc);
}