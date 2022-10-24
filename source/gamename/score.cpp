// COMP710 GP Framework 2022

// This include:
#include "score.h"

// Local includes:
#include "logmanager.h"

// Library includes:

Score::Score()
{
	m_iMaxScore = 0;
	m_iCurrentScore = 0;
}

Score::~Score()
{

}

void
Score::AddScore(int score)
{
	m_iCurrentScore += score;
}

void
Score::SetMaxScore(int maxScore)
{
	m_iMaxScore = maxScore;
}

float
Score::GetScorePercentage()
{
	//if (m_iMaxScore == 0.f)
	//{
	//	return 100.f;
	//}
	return (m_iCurrentScore / static_cast<float>(m_iMaxScore));
}

int 
Score::GetCurrentScore()
{
	return m_iCurrentScore;
}

bool
Score::HasPassed()
{
	return GetScorePercentage() >= 50.f;
}

void 
Score::Reset()
{
	m_iCurrentScore = 0;
}