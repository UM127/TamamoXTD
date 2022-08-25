#pragma once
class Player;

class Unit : public IGameObject
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

public:
	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3& GeUnitPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ���j�b�g�^�C�v�̎w��
	/// </summary>
	/// <param name="no"></param>
	void SetUnitTipe(const int no)
	{
		m_characterNo = no;
	}
	/// <summary>
	/// ���j�b�g�^�C�v�̎擾
	/// </summary>
	/// <returns></returns>
	const int GetUnitTipe()const
	{
		return m_characterNo;
	}
	void SetFirstsetup(const int setup)
	{
		m_SetUp=setup;
	}
	void SetPosition(Vector3 sp)
	{
		m_position = sp;
	}
private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimationClip_Punch,				//�ҋ@�A�j���[�V�����B	
		//enAnimationClip_Walk,				//�����A�j���[�V�����B
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


	Model m_model;
	ModelRender m_unit;                               //���j�b�g
	ModelRender m_attackcircle;							//�U���͈�
	Player* m_player;									//�v���C���[
	Animation m_animation;								// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;       //�L�����N�^�[�R���g���[���[�B
	Vector3 m_position = Vector3::Zero;				   // ���W
	Quaternion m_rotation = Quaternion::Identity;;     // ��]
	Vector3 m_scale = Vector3::One;	                   // �g�嗦
	CollisionObject* m_collisionObject;

	int m_playerState;
	int m_characterNo=0;
	float m_timer = 0.0f;
	//����Ōy�����邽�߂ɏo���ď���
	int m_SetUp = false;
};