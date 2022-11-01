#pragma once
class Player;
class Enemy;
class Unit;
class BackGround;
class GameCamera;
class EnemySpawn;
class GameUI;

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
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

private:
	BackGround* m_background;					    //�w�i�B
	EnemySpawn* m_enemyspawn;
	GameUI* m_gameui;
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
	//��������͉��Œǉ���������
private:
	void Try();

	int m_itemState = 0;

	int m_gage = 0;
	int m_gari = 0;
	int m_tea = 0;
	int m_syoyu = 0;
	int m_wasabi = 0;

	int m_hp=10;
	int m_Maxhp=10;


	GameCamera* m_gameCamera;
};

