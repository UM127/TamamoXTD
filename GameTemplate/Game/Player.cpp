#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

bool Player::Start()
{
	//アニメーションを読み込む
	m_animationClipArray[enAnimationClip_Idle].Load("Assets/animData/nonPBR/Idle.tka");
	m_animationClipArray[enAnimationClip_Idle].SetLoopFlag(true);
	//モデルの読み込み
	m_player.Init("Assets/modelData/model/nonPBR.tkm"
		, m_animationClipArray, enAnimationClip_Num, enModelUpAxisY);

	m_position.z = 0.0f;
	
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_rotation.SetRotationDegY(0.0f);
	m_rotation.AddRotationDegX(-180.0f);
	m_player.SetRotation(m_rotation);
	m_player.SetPosition(m_position);

	return true;
}

float a=0.0f;

void Player::Update()
{
	Vector3 moveSpeed;
	moveSpeed.x = g_pad[0]->GetLStickXF() * 120.0f;
	moveSpeed.z = g_pad[0]->GetLStickYF() * 120.0f;

	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/


	// 左スティック(キーボード：WASD)で平行移動。
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();
	a++;
	//m_rotation.AddRotationDegY(a);
	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player.SetPosition(m_position);
	m_player.SetRotation(m_rotation);
	m_player.Update();
}



void Player::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}