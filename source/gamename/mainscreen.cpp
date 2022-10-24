// COMP710 Peter An

// This include:
#include "mainscreen.h"

#include "inputsystem.h"
#include "renderer.h"
#include "sprite.h"

MainScreen::MainScreen()
	: m_pMainScreen(0)
	, m_pMainScreenText(0)
{

}

MainScreen::~MainScreen()
{
	delete m_pMainScreen;
	m_pMainScreen = 0;

	delete m_pMainScreenText;
	m_pMainScreenText = 0;
}

bool
MainScreen::Initialise(Renderer& renderer, FMOD::System* soundSystem)
{
	m_pMainScreen = renderer.CreateSprite("sprites\\MainScreen.jpg");
	m_pMainScreen->SetX(renderer.GetWidth() / 2);
	m_pMainScreen->SetY(renderer.GetHeight() / 2);
	m_pMainScreen->SetAlpha(0.8f);

	m_pMainScreenText = renderer.CreateSprite("sprites\\MainScreenText.png");
	m_pMainScreenText->SetX(renderer.GetWidth() / 2);
	m_pMainScreenText->SetY(renderer.GetHeight() / 2);

	return true;
}

bool 
MainScreen::GetIsPaused()
{
	return false;
}

void
MainScreen::Process(float deltaTime, InputSystem& inputSystem)
{

}

void
MainScreen::Draw(Renderer& renderer)
{
	m_pMainScreen->Draw(renderer);
	m_pMainScreenText->Draw(renderer);
}

void MainScreen::DebugDraw()
{

}