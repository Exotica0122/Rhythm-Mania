// COMP710 Peter An

// This include:
#include "scenerhythmmaniatest.h"

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

// Library includes:
#include <cassert>
#include <cstdlib>
#include <math.h> 

SceneRhythmManiaTest::SceneRhythmManiaTest()
	: m_pCursor(0)
	, m_bIsSongPause(false)
{
}

SceneRhythmManiaTest::~SceneRhythmManiaTest()
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
}

bool
SceneRhythmManiaTest::Initialise(Renderer& renderer, FMOD::System* soundSystem)
{
	m_pRenderer = &renderer;

	m_pSongClass = new Song();
	m_pSongClass->Initialise(renderer, soundSystem, "songs\\847812 J Pachelbel - Canon (Cranky Remix)\\J. Pachelbel - Canon (Cranky Remix) (lcfc) [Kalibe's Hard].osu");

	// init cursor
	m_pCursor = new Cursor();
	m_pCursor->Initialise(renderer);

	m_pBackGround = renderer.CreateSprite("BG.jpg");
	m_pBackGround->SetX(renderer.GetWidth() / 2);
	m_pBackGround->SetY(renderer.GetHeight() / 2);
	m_pBackGround->SetAlpha(0.33f);

	m_pScoreBar = renderer.CreateSprite("scorebar-bg.png");
	m_pScoreBar->SetX(renderer.GetWidth() / 2);
	m_pScoreBar->SetY(renderer.GetHeight() / 2);
	m_pScoreBar->SetScale(1.4f);

	m_pPauseScreen = renderer.CreateSprite("PauseScreen.png");
	m_pPauseScreen->SetX(renderer.GetWidth() / 2);
	m_pPauseScreen->SetY(renderer.GetHeight() / 2);

	return true;
}

void
SceneRhythmManiaTest::Process(float deltaTime, InputSystem& inputSystem)
{
	// Implement UI stuffs

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

	m_pSongClass->Process(deltaTime, inputSystem);
}

void
SceneRhythmManiaTest::DebugDraw()
{
	ImGui::Text("Scene: Rhythm Mania Test");
	m_pCursor->DebugDraw();
	m_pSongClass->DebugDraw();
}

void
SceneRhythmManiaTest::Draw(Renderer& renderer)
{
	m_pBackGround->Draw(renderer);
	m_pScoreBar->Draw(renderer);

	m_pSongClass->Draw(renderer);

	if (m_bIsSongPause)
	{
		m_pPauseScreen->Draw(renderer);
	}

	m_pCursor->Draw(renderer);
}