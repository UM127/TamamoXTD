#include "k2EngineLowPreCompile.h"
#include "ShadowRender.h"

namespace nsK2EngineLow {

	ShadowRender g_shadow;
	void ShadowRender::Init()
	{
        // シャドウマップ描画用のレンダリングターゲットを作成する
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shadowMap.Create(
            1024,// レンダリングターゲットの横幅
            1024,// レンダリングターゲットの縦幅
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );

        //
        ////【注目】シャドウマップ描画用のシェーダーを指定する。
        //teapotShadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
        //teapotShadowModelInitData.m_tkmFilePath = "Assets/modelData/debug/teapot.tkm";
        //teapotShadowModel.Init(teapotShadowModelInitData);
        //teapotShadowModel.UpdateWorldMatrix(
        //    { 0, 50, 100 },
        //    g_quatIdentity,
        //    g_vec3One
        //);
        ////影が落とされるモデル用のシェーダーを指定する。
        //bgModelInitData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
        ////シャドウマップを拡張SRVに設定する。
        //bgModelInitData.m_expandShaderResoruceView[0] = &shadowMap.GetRenderTargetTexture();
        ////ライトビュープロジェクション行列を拡張定数バッファに設定する。
        //bgModelInitData.m_expandConstantBuffer = (void*)&lightCamera.GetViewProjectionMatrix();
        //bgModelInitData.m_expandConstantBufferSize = sizeof(lightCamera.GetViewProjectionMatrix());
        //bgModelInitData.m_tkmFilePath = "Assets/modelData/stage/bg.tkm";

        //// シャドウマップを表示するためのスプライトを初期化する
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
        // 影描画用のライトカメラを作成する
        // step-2 影描画用のライトカメラを作成する
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
        // 影を生成したいモデルをシャドウマップに描画する
        //レンダリングターゲットをシャドウマップに変更する。
        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);

        //シャドウレンダーの処理を呼び出す。
        g_renderingEngine.ShadowRenderDraw(g_graphicsEngine->GetRenderContext());

        // 書き込み完了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);

        // 通常レンダリング
        // レンダリングターゲットをフレームバッファーに戻す
        rc.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
        
        //// ティーポットモデルを描画
        //teapotModel.SetPosition({ 0,50,100 });
        //teapotModel.Update();
        //teapotModel.Draw(rc);

        //// 背景を描画
        //bgModel.Draw(rc);

        //sprite.Update({ FRAME_BUFFER_W / -2.0f, FRAME_BUFFER_H / 2.0f,  0.0f }, g_quatIdentity, g_vec3One, { 0.0f, 1.0f });
        //sprite.Draw(rc);
        //
    }

}
