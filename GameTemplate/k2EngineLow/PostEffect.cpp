#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow {

	PostEffect g_postEffect;

	void PostEffect::Init()
	{

        mainRenderTarget.Create(
            1600,
            900,
            1,
            1,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_D32_FLOAT
        );

        //�𑜓x�A�~�b�v�}�b�v���x��
        luminanceRenderTarget.Create(
            1600,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
            900,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
            1,
            1,
            //�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            DXGI_FORMAT_D32_FLOAT
        );
	}

    void PostEffect::Render(RenderContext& rc)
    {
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.mainRenderTarget);

		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTarget(g_postEffect.mainRenderTarget);

		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(g_postEffect.mainRenderTarget);

		g_engine->ExecuteRender();

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.mainRenderTarget);



		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(g_postEffect.luminanceRenderTarget);

		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTarget(g_postEffect.luminanceRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(g_postEffect.luminanceRenderTarget);

		g_bloom.LuminanceSpriteDraw(rc);

		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(g_postEffect.luminanceRenderTarget);

		g_bloom.Blur(rc);

		g_bloom.Render(rc, mainRenderTarget);
		// step-5 ��ʂɕ\������郌���_�����O�^�[�Q�b�g�ɖ߂�
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);
		//g_bloom.Draw(rc);
		//�����ŃG�t�F�N�g�h���[�B
		EffectEngine::GetInstance()->Draw();
    }
}