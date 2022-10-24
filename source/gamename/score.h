// COMP710 GP Framework 2022
#ifndef __SCORE_H__
#define __SCORE_H__

// Local includes:


// Forward declarations:
class CircleManager;

// Class declaration:
class Score
{
	// Member methods:
public:
	Score();
	~Score();
	void AddScore(int score);
	void SetMaxScore(int maxScore);
	float GetScorePercentage();
	int GetCurrentScore();
	bool HasPassed();
	void Reset();
protected:
private:
	Score(const Score& score);
	Score& operator=(const Score& score);
	// Member data:

public:
protected:

private:
	int m_iMaxScore;
	int m_iCurrentScore;
};

#endif // __SCORE_H__