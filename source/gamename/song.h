// COMP710 GP Framework 2022
#ifndef __SONG_H__
#define __SONG_H__

// Local includes:

// Library includes:
#include "fmod.hpp"
#include <vector>
#include <string>

// Forward declarations:
class OsuParser;
class CircleManager;
class Score;
class Renderer;
class InputSystem;
class Sprite;

// Class declaration:
class Song
{
	// Member methods:
public:
	Song();
	~Song();
	bool Initialise(Renderer& renderer, FMOD::System* soundSystem, std::string diffName);
	void LoadSong();
	void PlaySong();
	void PauseSong();
	void Restart();
	void Process(float deltaTime, InputSystem& inputSystem);
	void DrawScore(Renderer& renderer);
	void DrawScorePercentage(Renderer& renderer);
	void DrawCombo(Renderer& renderer);
	void Draw(Renderer& renderer);
	void DebugDraw();
	bool GetIsPaused();
	int GetEndTime();
	int GetScore();
	float GetScorePercentage();
protected:
private:
	Song(const Song& song);
	Song& operator=(const Song& song);
	// Member data:

public:
protected:

private:
	OsuParser* m_pOsuParser;

	FMOD::System* m_pSoundSystem;

	FMOD::Sound* m_pSong;
	FMOD::Sound* m_pHitSound;
	FMOD::Sound* m_pMissSound;
	FMOD::Channel* m_pSongChannel;

	Sprite* m_pBackGround;

	Sprite* m_pScore0;
	Sprite* m_pScore1;
	Sprite* m_pScore2;
	Sprite* m_pScore3;
	Sprite* m_pScore4;
	Sprite* m_pScore5;
	Sprite* m_pScore6;
	Sprite* m_pScore7;
	Sprite* m_pScore8;
	Sprite* m_pScore9;

	Sprite* m_pPercentage;

	std::vector<Sprite*> m_pNumber;

	CircleManager* m_pCircleManager;
	Score* m_pScore;

	int m_iMaxScore;
	int m_iCurrentScore;

	bool m_bIsSongPause;
};

#endif // __SONG_H__