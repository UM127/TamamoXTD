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
	/// �J�n�̏���
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;
	void GameDelete();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

	void SetWorldStop(const int& stop)
	{
		m_worldstop = stop;
	}

	/// <summary>
	///���E���~�܂��Ă��邩���擾�B
	/// </summary>
	/// <returns>���E���~�܂��Ă��邩</returns>
	const int& GetWorldStop() const
	{
		return m_worldstop;
	}

	/// <summary>
	///���U���g�ɔ�Ԃ悤�ɐݒ�B
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
	///�N���A�����ݒ�B
	/// </summary>
	void SetClear()
	{
		m_clear = true;
	}
private:
	Score* m_score;
	BackGround* m_background;					    //�w�i�B
	EnemySpawn* m_enemyspawn;
	GameUI* m_gameui;
	Result* m_result;
	SoundSource* gameBGM;                      //�Q�[��BGM��ǂݍ���
	SpriteRender	m_spriteRender;
	FontRender      m_fontRender;					//�t�H���g�����_�[
	ModelRender     m_modelRender;					//���f�������_�[
	Player*        m_player;						//�v���C���[
	Enemy*			m_enemy;
	Unit*			m_unit=nullptr;							//���j�b�g	
	Vector3         m_pointligpos;                  //�|�C���g���C�g�̍��W
	Vector3         m_directionligColor={ 1.0f, 1.0f, 1.0f };		    //�Z�b�g����F
	Vector3			m_spPosition;					//�X�|�b�g���C�g�̃|�W�V����
	Vector3			m_spDirection;                  //�X�|�b�g���C�g�̕���

	SpriteRender    m_spriteHP;					//HP�΁[
private:

	int m_resultcreate = false;
	int m_clear = false;

	int m_hp=10;
	int m_Maxhp=10;

	int m_worldstop = false;
	int m_gamedelete = false;


	GameCamera* m_gameCamera;
};

