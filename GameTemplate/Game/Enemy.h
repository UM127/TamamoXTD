#pragma once
class EXP;
class Player;
class PlayerLevelManagement;

class Enemy : public IGameObject
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
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	/// <summary>
	/// HP����
	/// </summary>
	void EnemyHP();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();

private:
	ModelRender m_enemy;
	Player* m_player;
	EXP* m_exp;
	PlayerLevelManagement* m_plmanagement;
	Vector3 m_position = Vector3::Zero;				   //���W
	Vector3 m_playerposition;							//�v���C���[�̍��W
	Quaternion m_rotation = Quaternion::Identity;     //��]
	Vector3 m_scale = Vector3::One;	                   //�g�嗦
	Vector3 m_moveSpeed;							   //�ړ����x
	Vector3 m_forward = { 0.0f,0.0f,1.0f };                                 //�L�����N�^�[�̑O�����̃x�N�g��
	CollisionObject* m_collisionObject;
	SpriteRender m_mushhpbar;							//HP�o�[
};

