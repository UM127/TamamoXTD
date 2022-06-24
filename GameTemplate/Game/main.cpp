#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

const int NUM_DIRECTIONAL_LIGHT = 4; // ディレクションライトの数

//ブルーム
/// <summary>
/// ディレクションライト
/// </summary>
struct DirectionalLight
{
	Vector3 direction;  // ライトの方向
	float pad0;         // パディング
	Vector4 color;      // ライトのカラー
};

/// <summary>
/// ライト構造体
/// </summary>
struct Light
{
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT]; // ディレクションライト
	Vector3 eyePos;                 // カメラの位置
	float specPow;                  // スペキュラの絞り
	Vector3 ambinetLight;           // 環境光
};

const int NUM_WEIGHTS = 8;
/// <summary>
/// ブラー用のパラメーター
/// </summary>
struct SBlurParam
{
	float weights[NUM_WEIGHTS];
};
//ブおわ

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, 250.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });

	//ブ
	
     // step-1 メインレンダリングターゲットを作成する
    RenderTarget mainRenderTarget;
    mainRenderTarget.Create(
        1600,
        900,
        1,
        1,
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );
    // step-2 強い光のライトを用意する
    Light light;

    light.directionalLight[0].color.x = 5.8f;
    light.directionalLight[0].color.y = 5.8f;
    light.directionalLight[0].color.z = 5.8f;

    light.directionalLight[0].direction.x = 0.0f;
    light.directionalLight[0].direction.y = 0.0f;
    light.directionalLight[0].direction.z = -1.0f;
    light.directionalLight[0].direction.Normalize();

    light.ambinetLight.x = 0.5f;
    light.ambinetLight.y = 0.5f;
    light.ambinetLight.z = 0.5f;
    light.eyePos = g_camera3D->GetPosition();
    // モデルの初期化情報を設定する
    ModelInitData plModelInitData;

    // tkmファイルを指定する
    plModelInitData.m_tkmFilePath = "Assets/modelData/model/eggR.tkm";

    // シェーダーファイルを指定する
    plModelInitData.m_fxFilePath = "Assets/shader/sample3D.fx";

    // ユーザー拡張の定数バッファーに送るデータを指定する
    plModelInitData.m_expandConstantBuffer = &light;

    // ユーザー拡張の定数バッファーに送るデータのサイズを指定する
    plModelInitData.m_expandConstantBufferSize = sizeof(light);

    // レンダリングするカラーバッファーのフォーマットを指定する
    plModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    // 設定した初期化情報をもとにモデルを初期化する
    Model plModel;
    plModel.Init(plModelInitData);

    // step-3 輝度抽出用のレンダリングターゲットを作成
    RenderTarget luminnceRenderTarget;
    //解像度、ミップマップレベル
    luminnceRenderTarget.Create(
        1600,		//解像度はメインレンダリングターゲットと同じ。
        900,		//解像度はメインレンダリングターゲットと同じ。
        1,
        1,
        //【注目】カラーバッファのフォーマットを32bit浮動小数点にしている。
        DXGI_FORMAT_R32G32B32A32_FLOAT,
        DXGI_FORMAT_D32_FLOAT
    );
    // step-4 輝度抽出用のスプライトを初期化
    SpriteInitData luminanceSpriteInitData;
    //輝度抽出用のシェーダーのファイルパスを指定する。
    luminanceSpriteInitData.m_fxFilePath = "Assets/shader/samplePostEffect.fx";
    //頂点シェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
    //ピクセルシェーダーのエントリーポイントを指定する。
    luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
    //スプライトの幅と高さはluminnceRenderTargetと同じ。
    luminanceSpriteInitData.m_width = 1600;
    luminanceSpriteInitData.m_height = 900;
    //テクスチャはメインレンダリングターゲットのカラーバッファ。
    luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    //描き込むレンダリングターゲットのフォーマットを指定する。
    luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //作成した初期化情報をもとにスプライトを初期化する。
    Sprite luminanceSprite;
    luminanceSprite.Init(luminanceSpriteInitData);
    // step-5 ガウシアンブラーを初期化
    GaussianBlur gaussianBlur;
    gaussianBlur.Init(&luminnceRenderTarget.GetRenderTargetTexture());

    // step-6 ボケ画像を加算合成するスプライトを初期化
    SpriteInitData finalSpriteInitData;
    finalSpriteInitData.m_textures[0] = &gaussianBlur.GetBokeTexture();
    //解像度はmainRenderTargetの幅と高さ。
    finalSpriteInitData.m_width = 1600;
    finalSpriteInitData.m_height = 900;
    //ぼかした画像を、通常の2Dとしてメインレンダリングターゲットに描画するので、
    //2D用のシェーダーを使用する。
    finalSpriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";
    //ただし、加算合成で描画するので、アルファブレンディングモードを加算にする。
    finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
    //カラーバッファのフォーマットは例によって、32ビット浮動小数点バッファ。
    finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

    //初期化情報を元に加算合成用のスプライトを初期化する。
    Sprite finalSprite;
    finalSprite.Init(finalSpriteInitData);

    // step-7 テクスチャを貼り付けるためのスプライトを初期化する
    SpriteInitData spriteInitData;
    //テクスチャはmainRenderTargetのカラーバッファ。
    spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
    spriteInitData.m_width = 1600;
    spriteInitData.m_height = 900;
    //モノクロ用のシェーダーを指定する。
    spriteInitData.m_fxFilePath = "Assets/shader/sample2D.fx";
    //初期化オブジェクトを使って、スプライトを初期化する。
    Sprite copyToFrameBufferSprite;
    copyToFrameBufferSprite.Init(spriteInitData);
    //ブおわ

	//NewGO<Game>(0);

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

        //ブ
          // step-8 レンダリングターゲットをmainRenderTargetに変更する
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //レンダリングターゲットをクリア。
        renderContext.ClearRenderTargetView(mainRenderTarget);
        // step-9 mainRenderTargetに各種モデルを描画する
        plModel.Draw(renderContext);
        //レンダリングターゲットへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
        // step-10 輝度抽出
        renderContext.WaitUntilToPossibleSetRenderTarget(luminnceRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(luminnceRenderTarget);
        //レンダリングターゲットをクリア。
        renderContext.ClearRenderTargetView(luminnceRenderTarget);
        //輝度抽出を行う。
        luminanceSprite.Draw(renderContext);
        //レンダリングターゲットへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(luminnceRenderTarget);
        // step-11 ガウシアンブラーを実行する
        gaussianBlur.ExecuteOnGPU(renderContext, 20);
        // step-12 ボケ画像をメインレンダリングターゲットに加算合成
        renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
        //レンダリングターゲットを設定。
        renderContext.SetRenderTargetAndViewport(mainRenderTarget);
        //最終合成。
        finalSprite.Draw(renderContext);
        //レンダリングターゲットへの書き込み終了待ち。
        renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
        // step-13 メインレンダリングターゲットの絵をフレームバッファーにコピー
        renderContext.SetRenderTarget(
            g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
            g_graphicsEngine->GetCurrentFrameBuffuerDSV()
        );
        copyToFrameBufferSprite.Draw(renderContext);
        // ライトの強さを変更する
        light.directionalLight[0].color.x += g_pad[0]->GetLStickXF() * 0.5f;
        light.directionalLight[0].color.y += g_pad[0]->GetLStickXF() * 0.5f;
        light.directionalLight[0].color.z += g_pad[0]->GetLStickXF() * 0.5f;
        //ブおわ

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_k2EngineLow->ExecuteRender();

		// スプライトレンダーの描画処理を呼び出す。
		//g_renderingEngine.SpriteRenderDraw(renderContext);

		// フォントレンダーの描画処理を呼び出す。
		//g_renderingEngine.FontRenderDraw(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();

	}

	delete g_k2EngineLow;

	return 0;
}