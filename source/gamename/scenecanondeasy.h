// COMP710 GP Framework 2022
#ifndef __SCENECANONDEASY_H__
#define __SCENECANONDEASY_H__

#include "fmod.hpp"

// Local includes:
#include "scene.h"

// Forward declarations:
class Renderer;
class Ball;
class Cursor;
class OsuParser;
class CircleManager;
class Score;
class Song;
class Sprite;
class EndScreen;

// Class declaration:
class SceneCanonDEasy : public Scene
{
	// Member methods:
public:
	SceneCanonDEasy();
	virtual ~SceneCanonDEasy();
	virtual bool Initialise(Renderer& renderer, FMOD::System* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);
	virtual void DebugDraw();
	virtual bool GetIsPaused();

	void Restart();
	void Quit();

protected:
private:
	SceneCanonDEasy(const SceneCanonDEasy& sceneCanonDEasy);
	SceneCanonDEasy& operator=(const SceneCanonDEasy& sceneCanonDEasy);
	// Member data:
public:
protected:
	Renderer* m_pRenderer;

	FMOD::Sound* m_pSong;
	FMOD::Sound* m_pHitSound;
	FMOD::Sound* m_pMissSound;
	FMOD::Channel* m_pSongChannel;

	bool m_bIsSongPause;

	Cursor* m_pCursor;

	float m_fPlayTime;

	Song* m_pSongClass;
	EndScreen* m_pEndScreen;

	Sprite* m_pBackGround;
	Sprite* m_pScoreBar;
	Sprite* m_pPauseScreen;
	Sprite* m_pDifficultyText;

private:
};
#endif // __SCENECANONDEASY_H__