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
		Camera lightCamera;		// step-2 �e�`��p�̃��C�g�J�������쐬����
		Model bgModel;
		//ModelRender teapotModel;
		ModelInitData bgModelInitData;
		// step-3 �V���h�E�}�b�v�`��p�̃��f����p�ӂ���
		ModelInitData teapotShadowModelInitData;
		Model teapotShadowModel;
		Sprite sprite;
	};
	extern ShadowRender g_shadow;
}