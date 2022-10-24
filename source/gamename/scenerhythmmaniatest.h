// COMP710 GP Framework 2022
#ifndef __SCENERHYTHMMANIATEST_H__
#define __SCENERHYTHMMANIATEST_H__

#include <vector>
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

// Class declaration:
class SceneRhythmManiaTest : public Scene
{
	// Member methods:
public:
	SceneRhythmManiaTest();
	virtual ~SceneRhythmManiaTest();
	virtual bool Initialise(Renderer& renderer, FMOD::System* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();

protected:
	//void SpawnGoodBalls(int number);
	//void SpawnBadBalls(int number);

	//void CheckCollisions();
	//bool BallVsBall(Ball* p1, Ball* p2);
private:
	SceneRhythmManiaTest(const SceneRhythmManiaTest& sceneBouncingBalls);
	SceneRhythmManiaTest& operator=(const SceneRhythmManiaTest& sceneBouncingBalls);
	// Member data:
public:
protected:
	Renderer* m_pRenderer;
	//OsuParser* m_pOsuParser;

	FMOD::Sound* m_pSong;
	FMOD::Sound* m_pHitSound;
	FMOD::Sound* m_pMissSound;
	FMOD::Channel* m_pSongChannel;

	//CircleManager* m_pCircleManager;

	bool m_bIsSongPause;

	Cursor* m_pCursor;

	float m_fPlayTime;

	//Score* m_pScore;
	Song* m_pSongClass;

	Sprite* m_pBackGround;
	Sprite* m_pScoreBar;
	Sprite* m_pPauseScreen;

private:
};
#endif // __SCENERHYTHMMANIATEST_H__