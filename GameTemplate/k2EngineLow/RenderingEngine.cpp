#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	void RenderingEngine::SpriteRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Spriterenders) {
			renderObj->OnRender2D(rc);
		}
		//�o�^����Ă�`��I�u�W�F�N�g���N���A
		m_Spriterenders.clear();
	}
	void RenderingEngine::Execute(RenderContext& rc)
	{
		g_Lig.Update();
		
		//m_modelRenderCB.m_light = g_Light.GetLight();
		//m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_engine->ExecuteRender();

		g_Lig.Update();
		g_shadow.Render(rc);
		m_postEffect->Render(rc);
		//ShadowRenderDraw(rc);

		//g_postEffect.Render(rc);

		//Render2DDraw(rc);
		//m_renderobject.clear();
	}
	void RenderingEngine::FontRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Fontrenders) {
			renderObj->OnRender2D(rc);
		}
		//�o�^����Ă�`��I�u�W�F�N�g���N���A
		m_Fontrenders.clear();
	}
	void RenderingEngine::ShadowRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Shadowrenders) {
			renderObj->DrawShadow(rc);
		}
		//�o�^����Ă�`��I�u�W�F�N�g���N���A
		m_Shadowrenders.clear();
	}
	void RenderingEngine::Init()
	{
		m_postEffect = &g_postEffect;
		//m_shadowMapRender.Init();
		//m_modelRenderCB.m_light = g_Light.GetLight();
		//m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
	}
}