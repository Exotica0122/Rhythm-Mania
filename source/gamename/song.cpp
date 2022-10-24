// COMP710 GP Framework 2022

// This include:
#include "song.h"

// Local includes:
#include "osuparser.h"
#include "logmanager.h"
#include "circlemanager.h"
#include "score.h"
#include "inputsystem.h"
#include "renderer.h"
#include "sprite.h"
#include "imgui/imgui.h"


// Library includes:


Song::Song()
	: m_bIsSongPause(false)
{

}

Song::~Song()
{
	delete m_pOsuParser;
	m_pOsuParser = 0;

	delete m_pCircleManager;
	m_pCircleManager = 0;

	delete m_pScore;
	m_pScore = 0;

	for (Sprite* sprite : m_pNumber)
	{
		delete sprite;
	}
	m_pNumber.clear();

	delete m_pPercentage;
	m_pPercentage = 0;
}

bool
Song::Initialise(Renderer& renderer, FMOD::System* soundSystem, std::string diffName)
{
	m_pSoundSystem = soundSystem;
	m_pScore = new Score();

	// Osu Parsing Tester
	m_pOsuParser = new OsuParser();
	m_pOsuParser->LoadOsuFile(diffName);

	soundSystem->createSound("songs\\847812 J Pachelbel - Canon (Cranky Remix)\\audio.mp3", FMOD_DEFAULT, 0, &m_pSong);

	soundSystem->playSound(m_pSong, 0, false, &m_pSongChannel);
	m_pSongChannel->setPaused(true);

	m_pCircleManager = new CircleManager();
	m_pCircleManager->Initialise(renderer, soundSystem, m_pScore);
	m_pCircleManager->LoadCircles(m_pOsuParser->GetObjectPositions());

	m_pScore->SetMaxScore(m_pCircleManager->GetCircleCount() * 300);

	m_pScore0 = renderer.CreateSprite("skins\\Exotica1.2\\score-0.png");
	m_pScore1 = renderer.CreateSprite("skins\\Exotica1.2\\score-1.png");
	m_pScore2 = renderer.CreateSprite("skins\\Exotica1.2\\score-2.png");
	m_pScore3 = renderer.CreateSprite("skins\\Exotica1.2\\score-3.png");
	m_pScore4 = renderer.CreateSprite("skins\\Exotica1.2\\score-4.png");
	m_pScore5 = renderer.CreateSprite("skins\\Exotica1.2\\score-5.png");
	m_pScore6 = renderer.CreateSprite("skins\\Exotica1.2\\score-6.png");
	m_pScore7 = renderer.CreateSprite("skins\\Exotica1.2\\score-7.png");
	m_pScore8 = renderer.CreateSprite("skins\\Exotica1.2\\score-8.png");
	m_pScore9 = renderer.CreateSprite("skins\\Exotica1.2\\score-9.png");

	m_pNumber.push_back(m_pScore0);
	m_pNumber.push_back(m_pScore1);
	m_pNumber.push_back(m_pScore2);
	m_pNumber.push_back(m_pScore3);
	m_pNumber.push_back(m_pScore4);
	m_pNumber.push_back(m_pScore5);
	m_pNumber.push_back(m_pScore6);
	m_pNumber.push_back(m_pScore7);
	m_pNumber.push_back(m_pScore8);
	m_pNumber.push_back(m_pScore9);

	m_pPercentage = renderer.CreateSprite("skins\\Exotica1.2\\score-percent@2x.png");
	m_pPercentage->SetScale(0.6f);
	m_pPercentage->SetX(renderer.GetWidth() - m_pPercentage->GetWidth() / 2);
	m_pPercentage->SetY(renderer.GetHeight() - m_pPercentage->GetHeight() / 2);

	return true;
}

void
Song::LoadSong()
{
}

void
Song::PlaySong()
{
	m_pSongChannel->setPaused(false);
}

void
Song::PauseSong()
{
	m_pSongChannel->setPaused(true);
}

void Song::Restart()
{
	m_pSongChannel->stop();
	m_pSoundSystem->createSound("songs\\847812 J Pachelbel - Canon (Cranky Remix)\\audio.mp3", FMOD_DEFAULT, 0, &m_pSong);
	m_pSoundSystem->playSound(m_pSong, 0, false, &m_pSongChannel);
	m_pSongChannel->setPaused(true);
	m_pScore->Reset();
	m_pCircleManager->ResetCircles();
	
	m_bIsSongPause = true;
}

void
Song::Process(float deltaTime, InputSystem& inputSystem)
{
	if (m_bIsSongPause)
	{
		PauseSong();
		deltaTime = 0;
	}
	else
	{
		PlaySong();
	}

	m_pCircleManager->Process(deltaTime, inputSystem);

	if (inputSystem.GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
	{
		m_bIsSongPause = !m_bIsSongPause;
		m_pSongChannel->setPaused(m_bIsSongPause);
	}

	m_iCurrentScore = m_pScore->GetCurrentScore();
}

void
Song::DrawScore(Renderer& renderer)
{
	// Draw Score
	int iNums = m_iCurrentScore;

	if (iNums <= 0)
	{
		m_pNumber[0]->SetX(renderer.GetWidth() + m_pNumber[0]->GetWidth() / 2 - m_pNumber[0]->GetWidth());
		m_pNumber[0]->SetY(m_pNumber[0]->GetHeight() / 2);
		m_pNumber[0]->Draw(renderer);
		return;
	}
	int iNum = 0;
	int count = 1;
	while (iNums > 0) {
		iNum = iNums % 10;
		m_pNumber[iNum]->SetX((count * -m_pNumber[iNum]->GetWidth()) + renderer.GetWidth() + m_pNumber[iNum]->GetWidth() / 2);
		m_pNumber[iNum]->SetY(m_pNumber[iNum]->GetHeight() / 2);
		m_pNumber[iNum]->Draw(renderer);
		iNums = iNums / 10;
		count++;
	}
}

void
Song::DrawScorePercentage(Renderer& renderer)
{
	m_pPercentage->Draw(renderer);
	// Draw Score Percentage
	int iNums = static_cast<int>(m_pScore->GetScorePercentage() * 100);

	if (iNums <= 0)
	{
		m_pNumber[0]->SetX(-m_pNumber[0]->GetWidth() + renderer.GetWidth() + m_pNumber[0]->GetWidth() / 2 - m_pNumber[0]->GetWidth());
		m_pNumber[0]->SetY(renderer.GetHeight() - (m_pNumber[0]->GetHeight() / 2));
		m_pNumber[0]->Draw(renderer);
		return;
	}
	int iNum = 0.f;
	int count = 2;
	while (iNums > 0) {
		iNum = iNums % 10;
		m_pNumber[iNum]->SetX((count * -m_pNumber[iNum]->GetWidth()) + renderer.GetWidth() + m_pNumber[iNum]->GetWidth() / 2);
		m_pNumber[iNum]->SetY(renderer.GetHeight() - (m_pNumber[iNum]->GetHeight() / 2));
		m_pNumber[iNum]->Draw(renderer);
		iNums = iNums / 10;
		count++;
	}
}

void
Song::DrawCombo(Renderer& renderer)
{

}

bool 
Song::GetIsPaused()
{
	return m_bIsSongPause;
}

int 
Song::GetEndTime()
{
	return m_pCircleManager->GetEndTime();
}

int 
Song::GetScore()
{
	return m_pScore->GetCurrentScore();
}

float 
Song::GetScorePercentage()
{
	return m_pScore->GetScorePercentage();
}

void
Song::Draw(Renderer& renderer)
{
	m_pCircleManager->Draw(renderer);
	DrawScore(renderer);
	DrawCombo(renderer);
	DrawScorePercentage(renderer);
}

void
Song::DebugDraw()
{
	m_pCircleManager->DebugDraw();
	ImGui::Text("Percentage (%f)", m_pScore->GetScorePercentage());
}