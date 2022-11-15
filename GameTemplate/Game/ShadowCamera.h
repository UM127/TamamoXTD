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
	/// �����_�̃x�N�g�����擾����
	/// </summary>
	const Vector3& GetForwardVector() const
	{
		return m_toCameraPos;
	}

private:
	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B
	int m_CameraState = 0;
};