#pragma once

class Attack;
class Player;
class PlayerLevelManagement;

class AttackManagement : public IGameObject
{
public:
	/// <summary>
	/// �J�n�̏���
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �����U���̎������̏���
	/// </summary>
	void AttackMade();
private:
	Player* m_player;
	PlayerLevelManagement* m_plmanager;
	Attack* m_attack[3];				//�U��
	float m_attackmadetimer[5];
	int m_shotflag[4];
};

