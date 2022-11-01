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
private:
	FontRender m_fontrender;
	float m_spawntimer = 0.0f;
	float m_gametimer = 0.0f;
	int m_enemyspawnstage[10];//�G�̃X�|�[���̃��x��
};

