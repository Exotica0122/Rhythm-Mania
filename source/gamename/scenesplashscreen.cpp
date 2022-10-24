// COMP710 GP Framework 2022

// This include: 
#include "scenesplashscreen.h"

// Local includes: 
#include "renderer.h"
#include "sprite.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"

// Library includes: 
#include <cassert>

SceneSplashScreen::SceneSplashScreen()
	: m_pSplashScreen(0)
	, m_fCurrentTime(0.f)
{
}

SceneSplashScreen::~SceneSplashScreen()
{
	delete m_pSplashScreen;
	m_pSplashScreen = 0;
}

bool
SceneSplashScreen::Initialise(Renderer& renderer, FMOD::System* soundSystem)
{
	m_pSplashScreen = renderer.CreateSprite("sprites\\SplashScreen.png");
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();
	m_pSplashScreen->SetX(SCREEN_WIDTH / 2);
	m_pSplashScreen->SetY(SCREEN_HEIGHT / 2);
	m_pSplashScreen->SetAlpha(0);

	return true;
}

void
SceneSplashScreen::Process(float deltaTime, InputSystem& inputSystem)
{
	m_fCurrentTime += deltaTime;

	float alpha = m_pSplashScreen->GetAlpha();
	float newAlpha = alpha + (0.3f * deltaTime);

	if (m_fCurrentTime >= 5.f)
	{
		newAlpha = alpha - (0.5f * deltaTime);
	}

	m_pSplashScreen->SetAlpha(newAlpha);
}

void
SceneSplashScreen::DebugDraw()
{
}

void
SceneSplashScreen::Draw(Renderer& renderer)
{
	m_pSplashScreen->Draw(renderer);
}

bool 
SceneSplashScreen::GetIsPaused()
{
	return false;
}