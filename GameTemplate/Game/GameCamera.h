#pragma once

class Player;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

public:
	/// <summary>
	/// 注視点のベクトルを取得する
	/// </summary>
	const Vector3& GetForwardVector() const
	{
		return m_toCameraPos;
	}

private:
	Player* m_player;	//プレイヤー。
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	int m_CameraState = 0;
};