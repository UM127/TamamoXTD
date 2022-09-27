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
        // 影描画用のライトカメラを作成する
        Camera lightCamera;

        // カメラの位置を設定。これはライトの位置
        lightCamera.SetPosition(0, 500, 0);

        // カメラの注視点を設定。これがライトが照らしている場所
        lightCamera.SetTarget(0, 0, 0);

        // 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
        lightCamera.SetUp(1, 0, 0);

        // ライトビュープロジェクション行列を計算している
        lightCamera.Update();
    }
    void Shadow::CreateRT()
    {
        // step-1 シャドウマップ描画用のレンダリングターゲットを作成する
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shadowMap.Create(
            1024,//【注目】レンダリングターゲットの横幅
            1024,//【注目】レンダリングターゲットの縦幅
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );
        //カメラの位置を設定。これはライトの位置。
        lightCamera.SetPosition(0, 600, 0);
        //カメラの注視点を設定。これがライトが照らしている場所。
        lightCamera.SetTarget(0, 0, 0);
        //【注目】上方向を設定。今回はライトが真下を向いているので、X方向を上にしている。
        lightCamera.SetUp(1, 0, 0);
        //今回のサンプルでは画角を狭めにしておく。
        lightCamera.SetViewAngle(Math::DegToRad(20.0f));
        //ライトビュープロジェクション行列を計算している。
        lightCamera.Update();
        //【注目】シャドウマップ描画用のシェーダーを指定する。
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
        //影が落とされるモデル用のシェーダーを指定する。
        bgModelInitData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
        //シャドウマップを拡張SRVに設定する。
        bgModelInitData.m_expandShaderResoruceView[0] = &shadowMap.GetRenderTargetTexture();
        //ライトビュープロジェクション行列を拡張定数バッファに設定する。
        bgModelInitData.m_expandConstantBuffer = (void*)&lightCamera.GetViewProjectionMatrix();
        bgModelInitData.m_expandConstantBufferSize = sizeof(lightCamera.GetViewProjectionMatrix());
        bgModelInitData.m_tkmFilePath = "Assets/modelData/stage/bg.tkm";

        bgModel.Init(bgModelInitData);
    }
    void Shadow::ShadowDraw(RenderContext& rc)
    {
        // step-4 影を生成したいモデルをシャドウマップに描画する
        //レンダリングターゲットをシャドウマップに変更する。
        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);
    }
    void Shadow::Render(RenderContext& rc, RenderTarget& rt)
    {
        // 影モデルを描画
        teapotShadowModel.Draw(rc, lightCamera);

        // 書き込み完了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        // 通常レンダリング
        // レンダリングターゲットをフレームバッファーに戻す
        rc.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
    }
    void Shadow::Draw(RenderContext& rc)
    {
        // ティーポットモデルを描画
        teapotModel.Draw(rc);
        // step-2 影を受ける背景を描画
        bgModel.Draw(rc);
    }
}
