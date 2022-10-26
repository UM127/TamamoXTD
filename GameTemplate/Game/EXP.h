#pragma once
class Player;
class PlayerLevelManagement;

class EXP : public IGameObject
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
	/// ��]����
	/// </summary>
	void Rotation();
	void EXPProcess();
	/// <summary>
	/// �ʒu�̐ݒ�
	/// </summary>
	/// <param name="exppos"></param>
	void SetEXPPos(const Vector3& exppos)
	{
		m_exposition = exppos;
	}

private:
	Player* m_player;									//�v���C���[
	PlayerLevelManagement* m_plmanagement;
	ModelRender m_exp;
	Vector3 m_exposition = Vector3::Zero;			   //���W
	Quaternion m_exrotation = Quaternion::Identity;    //��]
	Vector3 m_scale = Vector3::One;	                   //�g�嗦
	Vector3 m_forward = { 0.0f,0.0f,1.0f };            //�L�����N�^�[�̑O�����̃x�N�g��
	CollisionObject* m_collisionObject;
};

