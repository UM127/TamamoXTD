#pragma once

class Player;

class Attack : public IGameObject
{
public:
	Attack();
	~Attack();
	//�ŏ��Ɉ�񂾂����s
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//�ړ����x�̐ݒ�
	void SetMoveSpeed(const Vector3& sms)
	{
		m_moveSpeed = sms;
	}
	/// <summary>
	/// �U���̎�ނ̐ݒ�
	/// </summary>
	/// <param name="attack"></param>
	void SetAttack(const int&attack)
	{
		m_attackno=attack;
	}
	/// <summary>
	/// �U���̍��W�̐ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	/// <summary>
	///���W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3& GetAttackPosition() const
	{
		return m_position;
	}

private:
	FontRender m_fontRender;                     //�����̕`��
	SphereCollider m_sphereCollider;		    //�~�^�̃R���C�_�[�B
	Vector3 m_playerposition;                  //�v���C���[�̈ʒu
	Vector3 m_enemyposition;                  //�G�̈ʒu
	Vector3 m_position;			              //���W�B
	Vector3 m_moveSpeed;					 //�ړ����x�B
	Vector3   m_bulletposition;             //�e�̈ʒu
	Vector3	m_efpos1;						//�G�t�F�N�g�p�̃|�W�V����
	Quaternion m_rotation;                  //�N�E�H�[�^�j�I��
	ModelRender m_modelRender;             //���f�������_�[
	Player* m_player;
	CollisionObject* m_collisionObject;
	float m_deletetimer = 0.0f;
	int bulletdelete = 0;
	int m_attackno = 0;
};

