#pragma once
namespace nsK2EngineLow {
	class Shadow
	{
	public:
		void Init();
		void InitBG();
		void CreateRT();
		void ShadowCamera();
		void Draw(RenderContext& rc);
		void ShadowDraw(RenderContext& rc);
		void Render(RenderContext& rc, RenderTarget& rt);
		RenderTarget shadowMap;
		Camera lightCamera;		// step-2 影描画用のライトカメラを作成する
		Model bgModel;
		ModelRender teapotModel;
		ModelInitData bgModelInitData;
		// step-3 シャドウマップ描画用のモデルを用意する
		ModelInitData teapotShadowModelInitData;
		Model teapotShadowModel;
	};
	extern Shadow g_shadow;
}