#pragma once
class EnemySpawn : public IGameObject
{
public:
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 敵のスポーン管理
	/// </summary>
	void EnemySpawnManagement();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 文字描画
	/// </summary>
	void Font();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	void ResetTimer()
	{
		m_gametimer = 0.0f;
	}
	const int& GetEnemyLevel()const
	{
		return m_enemyspawnstage;
	}
	void SetResultStop(const int& stop)
	{
		m_setresultstop = stop;
	}
private:
	FontRender m_fontrender;
	float m_spawntimer = 0.0f;
	float m_gametimer = 0.0f;
	int m_enemyspawnstage = 1;//敵のスポーンのレベル
	int m_setresultstop = false;
};

