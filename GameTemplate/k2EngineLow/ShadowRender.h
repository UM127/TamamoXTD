#pragma once
namespace nsK2EngineLow {
	class ShadowRender
	{
	public:
		void Init();
		void Draw(RenderContext& rc);
		void Render(RenderContext& rc);
		Texture& GetShadowMap()
		{
			return shadowMap.GetRenderTargetTexture();
		}
		Camera& GetLightCamera()
		{
			return lightCamera;
		}
		//void Render(RenderContext& rc, RenderTarget& rt);
	private:
		RenderTarget shadowMap;
		Camera lightCamera;		// step-2 影描画用のライトカメラを作成する
		Model bgModel;
		//ModelRender teapotModel;
		ModelInitData bgModelInitData;
		// step-3 シャドウマップ描画用のモデルを用意する
		ModelInitData teapotShadowModelInitData;
		Model teapotShadowModel;
		Sprite sprite;
	};
	extern ShadowRender g_shadow;
}