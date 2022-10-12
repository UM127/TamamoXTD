#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "Game.h"
#include "GameCamera.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"


bool Unit::Start()
{
	m_player = FindGO<Player>("player");

	//モデルの読み込み
	m_attackcircle.Init("Assets/modelData/AttackCircle.tkm");

	if (m_characterNo == 0)
	{
		////アニメーションを読み込む
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/Vanguard/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/Vanguard/Vanguard.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	if (m_characterNo == 1) {
		////アニメーションを読み込む
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/ElyByK/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/ElyByK/ElyByK.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	if (m_characterNo == 2) {
		m_animationClipArray[enAnimationClip_Punch].Load("Assets/animData/HerakliosByADizon/Punch.tka");
		m_animationClipArray[enAnimationClip_Punch].SetLoopFlag(true);
		m_unit.Init("Assets/modelData/model/HerakliosByADizon/HerakliosByADizon.tkm", false, m_animationClipArray, enAnimationClip_Num, enModelUpAxisZ);
	}
	m_attackcircle.SetScale({ 7.5f,1.0f,7.5f });
	m_attackcircle.SetPosition(m_position);
	m_attackcircle.Update();
	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//カプセル状のコリジョンを作成する。
	m_collisionObject->CreateCapsule(m_position,       //座標。
		Quaternion::Identity,                                   //回転。
		75.0f,													//球の大きさ(半径)。
		1.0f);                                                //球の大きさ(高さ)。
		//名前を付ける。
	m_collisionObject->SetName("attackcircle");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);
	m_unit.SetRotation(m_rotation);
	m_unit.SetPosition(m_position);
	m_unit.Update();

	return true;
}

void Unit::Update()
{
	if (m_SetUp == true)
	{
		DeleteGO(this);
	}
	m_unit.SetPosition(m_position);
	m_unit.SetRotation(m_rotation);
	m_unit.Update();
}



void Unit::Render(RenderContext& rc)
{
	m_unit.Draw(rc);
	m_attackcircle.Draw(rc);
}
