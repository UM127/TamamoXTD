#include "stdafx.h"
#include "EXP.h"
#include "Player.h"
#include "Enemy.h"
#include "PlayerLevelManagement.h"
#include "Game.h"
#include "Score.h"
//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

bool EXP::Start()
{
	m_player = FindGO<Player>("player");
	m_plmanagement = FindGO<PlayerLevelManagement>("playerlevelmanagement");
	m_exp.Init("Assets/modelData/model/EXP.tkm", false);
	m_exposition.y = 20.0f;
	m_exp.SetScale(0.5f, 0.5f, 0.5f);
	m_exp.SetRotation(m_exrotation);
	m_exp.SetPosition(m_exposition);
	m_exp.Update();

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	//Box状のコリジョンを作成する。
	m_collisionObject->CreateBox(m_exposition,       //座標。
		Quaternion::Identity,                                   //回転。
		{ 20.0f,20.0f,20.0f });                                                //Boxの大きさ。
	//名前を付ける。
	m_collisionObject->SetName("exp");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	return true;
}
void EXP::Update()
{
	//世界が止まっていないなら
	if (FindGO<Game>("game") != NULL)
	{
		if (FindGO<Game>("game")->GetWorldStop() == false)
		{
			Rotation();
			EXPProcess();
			//モデルの更新処理。
			m_exp.Update();
		}
	}
	else if (FindGO<Game>("game") == NULL)
	{
		DeleteGO(this);
	}
}
void EXP::Rotation()
{
	m_exrotation.AddRotationY(0.01f);
	m_exp.SetRotation(m_exrotation);
	m_exp.Update();
}
void EXP::EXPProcess()
{
	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		m_plmanagement->AddEXP();
		//衝突していたら。
		DeleteGO(m_collisionObject);
		DeleteGO(this);
	}
}

void EXP::Render(RenderContext& rc)
{
		m_exp.Draw(rc);
}