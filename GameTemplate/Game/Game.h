#pragma once
class Player;
class Enemy;
class Unit;
class BackGround;
class GameCamera;
class EnemySpawn;
class GameUI;
class Result;
class Score;

class Game : public IGameObject
{
public:
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	void GameDelete();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

	void SetWorldStop(const int& stop)
	{
		m_worldstop = stop;
	}

	/// <summary>
	///世界が止まっているかを取得。
	/// </summary>
	/// <returns>世界が止まっているか</returns>
	const int& GetWorldStop() const
	{
		return m_worldstop;
	}

	/// <summary>
	///リザルトに飛ぶように設定。
	/// </summary>
	void SetResult(const int&result)
	{
		m_resultcreate = result;
	}
	const int& GetResult() const
	{
		return 	m_resultcreate;
	}
	/// <summary>
	///クリア判定を設定。
	/// </summary>
	void SetClear()
	{
		m_clear = true;
	}
private:
	Score* m_score;
	BackGround* m_background;					    //背景。
	EnemySpawn* m_enemyspawn;
	GameUI* m_gameui;
	Result* m_result;
	SoundSource* gameBGM;                      //ゲームBGMを読み込む
	SpriteRender	m_spriteRender;
	FontRender      m_fontRender;					//フォントレンダー
	ModelRender     m_modelRender;					//モデルレンダー
	Player*        m_player;						//プレイヤー
	Enemy*			m_enemy;
	Unit*			m_unit=nullptr;							//ユニット	
	Vector3         m_pointligpos;                  //ポイントライトの座標
	Vector3         m_directionligColor={ 1.0f, 1.0f, 1.0f };		    //セットする色
	Vector3			m_spPosition;					//スポットライトのポジション
	Vector3			m_spDirection;                  //スポットライトの方向

	SpriteRender    m_spriteHP;					//HPばー
private:

	int m_resultcreate = false;
	int m_clear = false;

	int m_hp=10;
	int m_Maxhp=10;

	int m_worldstop = false;
	int m_gamedelete = false;


	GameCamera* m_gameCamera;
};

