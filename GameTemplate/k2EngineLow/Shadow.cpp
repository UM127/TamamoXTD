#include "k2EngineLowPreCompile.h"
#include "Shadow.h"

namespace nsK2EngineLow {

	Shadow g_shadow;
	void Shadow::Init()
	{
        ShadowCamera();
        CreateRT();
        InitBG();
	}
    void Shadow::ShadowCamera()
    {
        // �e�`��p�̃��C�g�J�������쐬����
        Camera lightCamera;

        // �J�����̈ʒu��ݒ�B����̓��C�g�̈ʒu
        lightCamera.SetPosition(0, 500, 0);

        // �J�����̒����_��ݒ�B���ꂪ���C�g���Ƃ炵�Ă���ꏊ
        lightCamera.SetTarget(0, 0, 0);

        // �������ݒ�B����̓��C�g���^���������Ă���̂ŁAX��������ɂ��Ă���
        lightCamera.SetUp(1, 0, 0);

        // ���C�g�r���[�v���W�F�N�V�����s����v�Z���Ă���
        lightCamera.Update();
    }
    void Shadow::CreateRT()
    {
        // step-1 �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬����
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shadowMap.Create(
            1024,//�y���ځz�����_�����O�^�[�Q�b�g�̉���
            1024,//�y���ځz�����_�����O�^�[�Q�b�g�̏c��
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );
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
        //�y���ځz�V���h�E�}�b�v�`��p�̃V�F�[�_�[���w�肷��B
        teapotShadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
        teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/debug/teapot.tkm";
        teapotShadowModel.Init(teapotShadowModelInitData);
        teapotShadowModel.UpdateWorldMatrix(
            { 0, 50, 0 },
            g_quatIdentity,
            g_vec3One
        );

        teapotModel.Init("Assets/modelData/debug/teapot.tkm");
        teapotModel.Update();
    }
    void Shadow::InitBG()
    {
        //�e�����Ƃ���郂�f���p�̃V�F�[�_�[���w�肷��B
        bgModelInitData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
        //�V���h�E�}�b�v���g��SRV�ɐݒ肷��B
        bgModelInitData.m_expandShaderResoruceView[0] = &shadowMap.GetRenderTargetTexture();
        //���C�g�r���[�v���W�F�N�V�����s����g���萔�o�b�t�@�ɐݒ肷��B
        bgModelInitData.m_expandConstantBuffer = (void*)&lightCamera.GetViewProjectionMatrix();
        bgModelInitData.m_expandConstantBufferSize = sizeof(lightCamera.GetViewProjectionMatrix());
        bgModelInitData.m_tkmFilePath = "Assets/modelData/stage/bg.tkm";

        bgModel.Init(bgModelInitData);
    }
    void Shadow::ShadowDraw(RenderContext& rc)
    {
        // step-4 �e�𐶐����������f�����V���h�E�}�b�v�ɕ`�悷��
        //�����_�����O�^�[�Q�b�g���V���h�E�}�b�v�ɕύX����B
        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);
    }
    void Shadow::Render(RenderContext& rc, RenderTarget& rt)
    {
        // �e���f����`��
        teapotShadowModel.Draw(rc, lightCamera);

        // �������݊����҂�
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        // �ʏ탌���_�����O
        // �����_�����O�^�[�Q�b�g���t���[���o�b�t�@�[�ɖ߂�
        rc.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
    }
    void Shadow::Draw(RenderContext& rc)
    {
        // �e�B�[�|�b�g���f����`��
        teapotModel.Draw(rc);
        // step-2 �e���󂯂�w�i��`��
        bgModel.Draw(rc);
    }
}
