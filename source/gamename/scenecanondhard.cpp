// COMP710 Peter An

// This include:
#include "scenecanondhard.h"

// Local includes:
#include "renderer.h"
#include "ball.h"
#include "circle.h"
#include "cursor.h"
#include "imgui/imgui.h"
#include "inputsystem.h"
#include "osuparser.h"
#include "logmanager.h"
#include "circlemanager.h"
#include "score.h"
#include "song.h"
#include "sprite.h"
#include "game.h"
#include "endscreen.h"

// Library includes:
#include <cassert>
#include <cstdlib>
#include <math.h> 

SceneCanonDHard::SceneCanonDHard()
	: m_pCursor(0)
	, m_bIsSongPause(false)
	, m_fPlayTime(0.f)
{
}

SceneCanonDHard::~SceneCanonDHard()
{
	delete m_pCursor;
	m_pCursor = 0;

	delete m_pSongClass;
	m_pSongClass = 0;

	delete m_pBackGround;
	m_pBackGround = 0;

	delete m_pScoreBar;
	m_pScoreBar = 0;

	delete m_pPauseScreen;
	m_pPauseScreen = 0;

	delete m_pDifficultyText;
	m_pDifficultyText = 0;

	delete m_pEndScreen;
	m_pEndScreen = 0;
}

bool
SceneCanonDHard::Initialise(Renderer& renderer, FMOD::System* soundSystem)
{
	renderer.CreateStaticText("J. Pachelbel - Canon (Cranky Remix) (lcfc) [Kalibe's Hard]", 25);
	m_pDifficultyText = renderer.CreateSprite("J. Pachelbel - Canon (Cranky Remix) (lcfc) [Kalibe's Hard]");
	m_pDifficultyText->SetX(m_pDifficultyText->GetWidth() / 2);
	m_pDifficultyText->SetY(m_pDifficultyText->GetHeight() / 2);

	m_pRenderer = &renderer;

	m_pEndScreen = new EndScreen();
	m_pEndScreen->Initialise(renderer);

	m_pSongClass = new Song();
	m_pSongClass->Initialise(renderer, soundSystem, "songs\\847812 J Pachelbel - Canon (Cranky Remix)\\J. Pachelbel - Canon (Cranky Remix) (lcfc) [Kalibe's Hard].osu");

	// init cursor
	m_pCursor = new Cursor();
	m_pCursor->Initialise(renderer);

	m_pBackGround = renderer.CreateSprite("sprites\\BG.jpg");
	m_pBackGround->SetX(renderer.GetWidth() / 2);
	m_pBackGround->SetY(renderer.GetHeight() / 2);
	m_pBackGround->SetAlpha(0.33f);

	m_pScoreBar = renderer.CreateSprite("sprites\\scorebar-bg.png");
	m_pScoreBar->SetX(renderer.GetWidth() / 2);
	m_pScoreBar->SetY(renderer.GetHeight() / 2);
	m_pScoreBar->SetScale(1.4f);

	m_pPauseScreen = renderer.CreateSprite("sprites\\PauseScreen.png");
	m_pPauseScreen->SetX(renderer.GetWidth() / 2);
	m_pPauseScreen->SetY(renderer.GetHeight() / 2);

	return true;
}

void
SceneCanonDHard::Process(float deltaTime, InputSystem& inputSystem)
{
	// Implement UI stuffs
	m_pCursor->Process(deltaTime, inputSystem);

	if (m_bIsSongPause)
	{
		deltaTime = 0;
	}

	// Game Mechanics

	m_fPlayTime += deltaTime;

	m_pCursor->FollowMouse(inputSystem);

	if (inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
	{
		m_bIsSongPause = !m_bIsSongPause;
		m_pSongChannel->setPaused(m_bIsSongPause);
	}

	if (inputSystem.GetKeyState(SDL_SCANCODE_BACKSPACE) == BS_PRESSED)
	{
		m_fPlayTime = 0.f;
		Quit();
	}

	if (m_pSongClass->GetEndTime() < m_fPlayTime)
	{
		// display total score
		m_pEndScreen->SetScore(m_pSongClass->GetScore());
		m_pEndScreen->SetScorePercentage(m_pSongClass->GetScorePercentage());
		m_bIsSongPause = false;
	}

	m_pSongClass->Process(deltaTime, inputSystem);
}

void
SceneCanonDHard::Quit()
{
	if (m_pSongClass->GetIsPaused())
	{
		m_pSongClass->Restart();
	}
}

bool
SceneCanonDHard::GetIsPaused()
{
	return m_bIsSongPause;
}

void
SceneCanonDHard::DebugDraw()
{
	ImGui::Text("Scene: Canon in D - Hard");
	m_pCursor->DebugDraw();
	m_pSongClass->DebugDraw();
	ImGui::Text("Play Time: (%f)", m_fPlayTime);
	ImGui::Text("End Time: (%d)", m_pSongClass->GetEndTime());
}

void
SceneCanonDHard::Draw(Renderer& renderer)
{
	m_pBackGround->Draw(renderer);
	m_pScoreBar->Draw(renderer);

	m_pSongClass->Draw(renderer);

	if (m_bIsSongPause)
	{
		m_pPauseScreen->Draw(renderer);
	}

	if (m_pSongClass->GetEndTime() < m_fPlayTime)
	{
		m_pEndScreen->Draw(renderer);
	}

	m_pDifficultyText->Draw(renderer);
	m_pCursor->Draw(renderer);
}