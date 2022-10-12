#include "k2EngineLowPreCompile.h"
#include "ShadowRender.h"

namespace nsK2EngineLow {

	ShadowRender g_shadow;
	void ShadowRender::Init()
	{
        // �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shadowMap.Create(
            1024,// �����_�����O�^�[�Q�b�g�̉���
            1024,// �����_�����O�^�[�Q�b�g�̏c��
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );

        //
        ////�y���ځz�V���h�E�}�b�v�`��p�̃V�F�[�_�[���w�肷��B
        //teapotShadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
        //teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/debug/teapot.tkm";
        //teapotShadowModel.Init(teapotShadowModelInitData);
        //teapotShadowModel.UpdateWorldMatrix(
        //    { 0, 50, 100 },
        //    g_quatIdentity,
        //    g_vec3One
        //);
        ////�e�����Ƃ���郂�f���p�̃V�F�[�_�[���w�肷��B
        //bgModelInitData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
        ////�V���h�E�}�b�v���g��SRV�ɐݒ肷��B
        //bgModelInitData.m_expandShaderResoruceView[0] = &shadowMap.GetRenderTargetTexture();
        ////���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�ɐݒ肷��B
        //bgModelInitData.m_expandConstantBuffer = (void*)&lightCamera.GetViewProjectionMatrix();
        //bgModelInitData.m_expandConstantBufferSize = sizeof(lightCamera.GetViewProjectionMatrix());
        //bgModelInitData.m_tkmFilePath = "Assets/modelData/stage/bg.tkm";

        //// �V���h�E�}�b�v��\�����邽�߂̃X�v���C�g������������
        //SpriteInitData spriteInitData;
        //spriteInitData.m_textures[0] = &shadowMap.GetRenderTargetTexture();
        //spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
        //spriteInitData.m_width = 256;
        //spriteInitData.m_height = 256;

        //sprite.Init(spriteInitData);

        //teapotModel.Init("Assets/modelData/debug/teapot.tkm");
        //teapotModel.Update();
        //bgModel.Init(bgModelInitData);
        
	}
    void ShadowRender::Render(RenderContext& rc)
    {
        // �e�`��p�̃��C�g�J�������쐬����
        // step-2 �e�`��p�̃��C�g�J�������쐬����
        //�J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu�B
        lightCamera.SetPosition(0, 600, 0);
        //�J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ�B
        lightCamera.SetTarget(0, 0, 0);
        //�y���ځz�������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���B
        lightCamera.SetUp(1, 0, 0);
        //����̃T���v���ł͉�p�����߂ɂ��Ă����B
        lightCamera.SetViewAngle(Math::DegToRad(20.0f));
        //���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���B
        lightCamera.Update();
        // �e�𐶐����������f�����V���h�E�}�b�v�ɕ`�悷��
        //�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����B
        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);

        //�V���h�E�����_�[�̏������Ăяo���B
        g_renderingEngine.ShadowRenderDraw(g_graphicsEngine->GetRenderContext());

        // �������݊����҂�
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        // �ʏ탌���_�����O
        // �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�[�ɖ߂�
        rc.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
        
        //// �e�B�[�|�b�g���f����`��
        //teapotModel.SetPosition({ 0,50,100 });
        //teapotModel.Update();
        //teapotModel.Draw(rc);

        //// �w�i��`��
        //bgModel.Draw(rc);

        //sprite.Update({ FRAME_BUFFER_W / -2.0f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
        //sprite.Draw(rc);
        //
    }

}
