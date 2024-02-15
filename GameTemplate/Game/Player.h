#pragma once

class Unit;
class Attack;
class AttackManagement;
class PlayerLevelManagement;

class Player : public IGameObject
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
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();
	/// <summary>
	/// �A�j���[�V�����Ǘ��֐�
	/// </summary>
	void AnimationManagement();
	/// <summary>
	/// �ʒu�̐ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
public:
	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3& GetPlayerPosition()
	{
		return m_position;
	}
	/// <summary>
	/// �v���C���[�̑O�����̃x�N�g��
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPlayerForward()
	{
		return m_forward;
	}
	const Quaternion& GetPlayerRot()
	{
		return m_rotation;
	}

	const Vector3& GetSideVector()
	{
		return m_side;
	}
	/// <summary>
	/// �L�����N�^�[�R���g���[���[���擾�B
	/// </summary>
	/// <returns>�L�����N�^�[�R���g���[���[�B</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}


private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimationClip_Idle,				//�ҋ@�A�j���[�V�����B	
		enAnimationClip_Walk,				//�����A�j���[�V�����B
		//enAnimationClip_Run,				//����A�j���[�V�����B
		//enAnimationClip_Attack1,			//�U���A�j���[�V�����B
		//enAnimationClip_Attack2,			//�U���A�j���[�V�����B
		//enAnimationClip_Attack3,			//�U���A�j���[�V�����B
		//enAnimationClip_MagicAttack,		//���@�U���A�j���[�V�����B
		//enAnimationClip_HitDamage1,			//��_���[�W�A�j���[�V�����B
		//enAnimationClip_HitDamage2,			//��_���[�W�A�j���[�V�����B
		//enAnimationClip_Down1,				//HP��0�B
		//enAnimationClip_Down2,				//HP��0�B
		//enAnimationClip_Down3,				//HP��0�B
		//enAnimationClip_PushLever,			//���o�[�������A�j���[�V�����B
		//enAnimationClip_Winner,				//�����A�j���[�V�����B
		enAnimationClip_Num,				//�A�j���[�V�����̐��B
	};

	PlayerLevelManagement* m_plmanagement;

	ModelRender m_player;                               //�v���C���[
	Animation m_animation;								// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;       //�L�����N�^�[�R���g���[���[�B
	Vector3 m_position= Vector3::Zero;				   //���W
	Quaternion m_rotation = Quaternion::Identity;     //��]
	Vector3 m_scale=Vector3::One;	                   //�g�嗦
	Vector3 m_moveSpeed;							   //�ړ����x
	Vector3 m_forward = {0.0f,0.0f,1.0f};                                 //�L�����N�^�[�̑O�����̃x�N�g��
	Vector3 m_up = { 0.0f,1.0f,0.0f };
	Vector3 m_side=Vector3::AxisX;
	CollisionObject* m_collisionObject;

	Attack* m_attack[3];				//�U��
	AttackManagement* m_attackmanagement;				//�U���̊Ǘ�

	int m_playerstate;
	int m_attackstate = false;			//�U���\���s�\��
	int m_hp = 1;
	float m_attackmadetimer[5];
	float m_attackcooltime[5];
	float m_timer = 0.0f;
};