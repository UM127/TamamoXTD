#include "stdafx.h"
#include "system/system.h"
#include "Game.h"
#include "Title.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;


/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("KinokoSurvivors"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 200.0f, 300.0f });
	g_camera3D->SetTarget({ 0.0f, 100.0f, 0.0f });

	g_postEffect.Init();
	g_Lig.Init();
	g_shadow.Init();
	g_bloom.Init();
	g_renderingEngine.Init();

	auto title= NewGO<Title>(0, "title");
	//auto game = NewGO<Game>(0, "game");

	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();


		//g_k2EngineLow->ExecuteRender();
		g_renderingEngine.Execute(renderContext);

		// スプライトレンダーの描画処理を呼び出す。
		g_renderingEngine.SpriteRenderDraw(renderContext);

		// フォントレンダーの描画処理を呼び出す。
		g_renderingEngine.FontRenderDraw(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();

	}

	delete g_k2EngineLow;

	return 0;
}