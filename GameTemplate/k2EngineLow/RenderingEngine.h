#pragma once

namespace nsK2EngineLow {

	class RenderingEngine :public Noncopyable
	{
	public:
		void Init();
		/// <summary>
		/// 描画オブジェクトを追加。
		/// </summary>
		/// <param name="renderObject"></param>
		void AddRenderObject(SpriteRender* renderObject)
		{
			m_Spriterenders.push_back(renderObject);
		}
		
		void AddRenderObject(FontRender* renderObject)
		{
			m_Fontrenders.push_back(renderObject);
		}

		void Execute(RenderContext& rc);

		void SpriteRenderDraw(RenderContext& rc);
		
		void FontRenderDraw(RenderContext& rc);
		

	private:
		std::vector<FontRender*> m_Fontrenders;
		std::vector<SpriteRender*> m_Spriterenders;
		PostEffect* m_postEffect = &g_postEffect;
		RenderTarget m_mainRenderTarget;
	};

	extern RenderingEngine g_renderingEngine;
}