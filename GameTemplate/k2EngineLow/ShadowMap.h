#pragma once
namespace nsK2EngineLow {
	class ShadowMap
	{
	public:
		void Init();

		void Render(RenderContext& rc, RenderTarget& rt);

		Texture& GetShadowMap()
		{
			return shadowMap.GetRenderTargetTexture();
		}
		Camera& GetLightCamera()
		{
			return m_lightCamera;
		}
	private:
		RenderTarget shadowMap;
		Camera m_lightCamera;
	};
}
