#include "stdafx.h"
#include "BackGround.h"

#include "Game.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	m_backGround.Init("Assets/modelData/stage/grassfloor.tkm",true);
	m_backGround.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_backGround.SetPosition(Vector3(0.0f, -1.0f, 0.0f));
	m_backGround.SetShadowReciverBG();
	//m_backGround.ShadowInit("Assets/modelData/stage/bg.tkm", true);
	//m_backGround.Init("Assets/modelData/stage/bg.tkm");
	//m_backGround.SetBGShadowflag();

	//	m_backGround.SetScale(m_scale);
	//	m_backGround.Update();
	//PhysicsStaticObjectを初期化。
	m_physicsStaticObject.CreateFromModel(
		m_backGround.GetModel(),
		m_backGround.GetModel().GetWorldMatrix());
	//当たり判定の可視化。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
}
