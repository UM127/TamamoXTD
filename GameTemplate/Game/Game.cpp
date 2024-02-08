#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include "GameUI.h"
#include "Result.h"

bool Game::Start()
{
	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player>(0, "player");
	//エネミー出現の管理をするクラス
	m_enemyspawn = NewGO<EnemySpawn>(0, "enemyspawn");
	//背景オブジェクトを作成する。
	m_background = NewGO<BackGround>(0, "background");
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//ゲームUIの生成
	m_gameui = NewGO<GameUI>(0, "gameui");
	return true;
}
void Game::Update()
{
	if (m_resultcreate == true && m_clear == true)
	{
		//ゴミ
		////リザルトを作る。ゲームを停止する。リザルトにクリア判定を追加
		//m_worldstop = true;
		//m_result = NewGO<Result>(0, "result2222");
		//m_result->SetClear();
	}
	else
	{
		//ゴミ
		////リザルトを作る。ゲームを停止する。
		//m_worldstop = true;
		////m_result = NewGO<Result>(0, "result");
	}

	// 左スティック(キーボード：WASD)で平行移動。
	//m_pointligpos.x += g_pad[0]->GetLStickXF();
	//m_pointligpos.y += g_pad[0]->GetLStickYF();
	//g_directionLig.SetPointPos(m_pointligpos);
	//m_pointligpos.z += g_pad[0]->GetLStickYF();
	//m_pointligpos.y = 50.0f;
	//g_Lig.SetPointPos(m_pointligpos);
	///*
	////ディレクションライトの当たる方向とカラーをセットできちゃいます
	//g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	//g_directionLig.SetLigColor({ 0.5f,0.5f,0.5f });
	//*/
	//g_Lig.SetPointPos(m_pointligpos);

	//
	//g_Lig.SetPointColor({ 0.0f,0.0f,0.0f });

	//m_spPosition.x = 0.0f;
	//g_Lig.SetSpotPos(m_spPosition);//スポットライトの位置を設定


	////Aボタンを押したら,光増加。
	//if (g_pad[0]->IsPress(enButtonA))
	//{
	//	m_directionligColor.x +=0.1f;
	//	m_directionligColor.y += 0.1f;
	//	m_directionligColor.z += 0.1f;
	//}
	////Bボタンを押したら、光減少。
	//else if (g_pad[0]->IsPress(enButtonB))
	//{
	//	m_directionligColor.x -= 0.1f;
	//	m_directionligColor.y -= 0.1f;
	//	m_directionligColor.z -= 0.1f;
	//}
	//m_directionligColor.x = 1.5f;
	//m_directionligColor.y = 1.5f;
	//m_directionligColor.z = 1.5f;
	//g_Lig.SetLigColor({ m_directionligColor });

	//HPが0より減っていたら。
	if (m_hp < 0)
	{
		//HPを0にする。
		m_hp = 0;
	}
	Vector3 scale = Vector3::One;
	scale.x = float(m_hp) / float(m_Maxhp);

	m_spriteHP.SetScale(scale);

	//更新処理。
	m_spriteHP.Update();
}
void Game::Render(RenderContext& rc)
{
	//m_spriteRender.Draw(rc);                 //タイトルの描画
	//m_spriteHP.Draw(rc);
	//m_fontRender.Draw(rc);
	//m_modelRender.Draw(rc);
}