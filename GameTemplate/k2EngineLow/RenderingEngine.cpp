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
		//登録されてる描画オブジェクトをクリア
		m_Spriterenders.clear();
	}
	void RenderingEngine::Execute(RenderContext& rc)
	{
		g_directionLig.Update();
		
		//m_modelRenderCB.m_light = g_Light.GetLight();
		//m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_engine->ExecuteRender();
		//ShadowMapDraw(rc);

		m_postEffect->Render(rc);

		//Render2DDraw(rc);
		//m_renderobject.clear();
	}
	void RenderingEngine::FontRenderDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_Fontrenders) {
			renderObj->OnRender2D(rc);
		}
		//登録されてる描画オブジェクトをクリア
		m_Fontrenders.clear();
	}
	void RenderingEngine::Init()
	{
		m_postEffect = &g_postEffect;
		//m_shadowMapRender.Init();
		//m_modelRenderCB.m_light = g_Light.GetLight();
		//m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
	}
}