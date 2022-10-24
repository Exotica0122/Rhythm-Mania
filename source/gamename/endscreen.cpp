// COMP710 GP Framework 2022

// This include:
#include "endscreen.h"
#include "renderer.h"
#include "sprite.h"

// Library includes:
#include <iostream>

EndScreen::EndScreen()
	: m_pEndScreen(0)
{

}

EndScreen::~EndScreen()
{
	delete m_pEndScreen;
	m_pEndScreen = 0;

	delete m_pWinText;
	m_pWinText = 0;

	delete m_pLoseText;
	m_pLoseText = 0;
}

bool
EndScreen::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	m_pEndScreen = renderer.CreateSprite("sprites\\EndScreen.png");
	m_pEndScreen->SetX(renderer.GetWidth() / 2);
	m_pEndScreen->SetY(renderer.GetHeight() / 2);

	m_pWinText = renderer.CreateSprite("sprites\\Win.png");
	m_pWinText->SetX(renderer.GetWidth() / 2);
	m_pWinText->SetY(renderer.GetHeight() / 2);

	m_pLoseText = renderer.CreateSprite("sprites\\Lose.png");
	m_pLoseText->SetX(renderer.GetWidth() / 2);
	m_pLoseText->SetY(renderer.GetHeight() / 2);

	return true;
}

void
EndScreen::DebugDraw()
{

}

void
EndScreen::Draw(Renderer& renderer)
{
	m_pEndScreen->Draw(renderer);
	if (m_fScorePercentage > 0.5f)
	{
		m_pWinText->Draw(renderer);
	}
	else
	{
		m_pLoseText->Draw(renderer);
	}
}

void
EndScreen::SetScore(int score)
{
	m_iScore = score;
}

void
EndScreen::SetScorePercentage(float scorePercentage)
{
	m_fScorePercentage = scorePercentage;
}