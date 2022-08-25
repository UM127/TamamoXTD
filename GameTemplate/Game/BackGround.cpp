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
	m_backGround.Init("Assets/modelData/stage/stage.tkm");
	m_backGround.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_backGround.SetPosition(Vector3(0.0f, -1.0f, 0.0f));
	//m_backGround.Init("Assets/modelData/stage/bg.tkm");

	//	m_backGround.SetScale(m_scale);
	//	m_backGround.Update();
	//PhysicsStaticObject���������B
	m_physicsStaticObject.CreateFromModel(
		m_backGround.GetModel(),
		m_backGround.GetModel().GetWorldMatrix());
	//�����蔻��̉����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
}
