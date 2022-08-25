#pragma once

class Unit;

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
	/// �����`��
	/// </summary>
	void Font();
	/// <summary>
	/// �����p�̃{�b�N�X�̈ړ�����
	/// </summary>
	void SummonBoxMove()
	{
		//�����p�̃{�b�N�X����Ƀv���C���[�̑O�ɂ���悤�ɂ���B
		m_summonboxpos = m_position;
		m_summonboxpos += m_forward*70.0f;
		m_summonboxcollisionObject = m_summonboxpos;

		m_summonbox.SetPosition(m_summonboxpos);
		m_summonbox.Update();
		m_collisionObject->SetPosition(m_summonboxcollisionObject);
		m_collisionObject->Update();
	}
	/// <summary>
	/// ���j�b�g�I���֐�
	/// </summary>
	void SelectUnittype()
	{
		//�I������Ă郆�j�b�g���O�ȊO��LB1�������ꂽ�Ƃ��ԍ���-1����
		if (m_summonUnitNo != 0 && g_pad[0]->IsTrigger(enButtonLB1))
		{
			m_summonUnitNo--;
		}
		//�I������Ă郆�j�b�g�����������RB1�������ꂽ�Ƃ��ԍ���+1����
		if (m_summonUnitNo<m_UnitMaxnum&& g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_summonUnitNo++;
		}
	}

public:
	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3& GetPlayerPosition() const
	{
		return m_position;
	}



private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimationClip_Idle,				//�ҋ@�A�j���[�V�����B	
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

	Unit* m_unit = nullptr;

	ModelRender m_player;                               //�v���C���[
	ModelRender m_summonbox;							//�����p�̃{�b�N�X
	FontRender m_fontRender;							//�t�H���g�����_�[
	FontRender m_fontRender3;							//�t�H���g�����_�[
	Animation m_animation;								// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimationClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;       //�L�����N�^�[�R���g���[���[�B
	Vector3 m_position= Vector3::Zero;				   //���W
	Quaternion m_rotation = Quaternion::Identity;     //��]
	Vector3 m_scale=Vector3::One;	                   //�g�嗦
	Vector3 m_moveSpeed;							   //�ړ����x
	Vector3 m_summonboxpos = Vector3::Zero;					//�����p�̃{�b�N�X�̈ʒu
	Vector3 m_summonboxcollisionObject = Vector3::Zero;		//�����p�̃{�b�N�X�̃R���W�����̈ʒu
	Vector3 m_forward;                                 //�L�����N�^�[�̑O�����̃x�N�g��
	CollisionObject* m_collisionObject;

	int m_UnitMaxnum = 2;//���j�b�g�ԍ��̍ő�l
	int m_summonUnitNo = 0;
	int m_playerState;
	float m_timer = 0.0f;
};