#pragma once
class EnemySpawn : public IGameObject
{
public:
	/// <summary>
	/// �J�n�̏���
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �G�̃X�|�[���Ǘ�
	/// </summary>
	void EnemySpawnManagement();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	/// <summary>
	/// �����`��
	/// </summary>
	void Font();
	/// <summary>
	/// �`�揈��
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
	int m_enemyspawnstage = 1;//�G�̃X�|�[���̃��x��
	int m_setresultstop = false;
};

