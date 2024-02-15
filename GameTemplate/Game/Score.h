#pragma once
class Score : public IGameObject
{
public:
	void Update();
	void AddScore()
	{
		m_score++;
	}
	void ScoreKill()
	{
		m_scorekill = true;
	}
	const int& GetScore()
	{
		return m_score;
	}
	int m_score = 0;
	int m_scorekill = false;
};

