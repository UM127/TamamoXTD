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
		Camera lightCamera;		// step-2 �e�`��p�̃��C�g�J�������쐬����
		Model bgModel;
		ModelRender teapotModel;
		ModelInitData bgModelInitData;
		// step-3 �V���h�E�}�b�v�`��p�̃��f����p�ӂ���
		ModelInitData teapotShadowModelInitData;
		Model teapotShadowModel;
	};
	extern Shadow g_shadow;
}