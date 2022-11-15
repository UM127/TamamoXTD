#pragma once

class ShadowCamera :public IGameObject
{
public:
	ShadowCamera();
	~ShadowCamera();
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
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	int m_CameraState = 0;
};