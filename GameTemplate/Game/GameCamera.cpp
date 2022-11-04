#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game.h"

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	//m_toCameraPos.Set(0.0f, 150.0f, 800.0f);
	m_toCameraPos.Set(0.0f, 70.0f, 200.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("player");

	//近平面を設定する。
	g_camera3D->SetNear(5.0f);
	//遠平面を設定する。
	g_camera3D->SetFar(13000.0f);
	return true;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->GetPlayerPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y = 50.0f;
	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	//float x = g_pad[0]->GetRStickXF();
	//float y = g_pad[0]->GetRStickYF();
	////Y軸周りの回転
	Quaternion qRot;
	//qRot.SetRotationDeg(Vector3::AxisY, 0.9f * x);
	//qRot.Apply(m_toCameraPos);
	////X軸周りの回転。
	//Vector3 axisX;
	//axisX.Cross(Vector3::AxisY, m_toCameraPos);
	//axisX.Normalize();
	//qRot.SetRotationDeg(axisX, 0.9f * y);
	qRot.SetRotation(Vector3::AxisX,180.0f);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	g_shadow.SetLightCameraTarget(target);
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}
