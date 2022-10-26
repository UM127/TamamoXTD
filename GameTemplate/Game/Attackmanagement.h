#pragma once

class Attack;
class Player;
class PlayerLevelManagement;

class AttackManagement : public IGameObject
{
public:
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 自動攻撃の周期等の処理
	/// </summary>
	void AttackMade();
private:
	Player* m_player;
	PlayerLevelManagement* m_plmanager;
	Attack* m_attack[3];				//攻撃
	float m_attackmadetimer[5];
	int m_shotflag[4];
};

