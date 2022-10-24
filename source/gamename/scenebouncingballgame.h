// COMP710 GP Framework 2022
#ifndef __SCENEBOUNCINGBALLGAME_H__
#define __SCENEBOUNCINGBALLGAME_H__

#include <vector>

// Local includes:
#include "scene.h"

// Forward declarations:
class Renderer;
class Ball;

// Class declaration:
class SceneBouncingBallGame : public Scene
{
	// Member methods:
public:
	SceneBouncingBallGame();
	virtual ~SceneBouncingBallGame();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void Draw(Renderer& renderer);

	virtual void DebugDraw();


protected:
	void SpawnGoodBalls(int number);
	void SpawnBadBalls(int number);

	void CheckCollisions();
	bool BallVsBall(Ball* p1, Ball* p2);
private:
	SceneBouncingBallGame(const SceneBouncingBallGame& sceneBouncingBalls);
	SceneBouncingBallGame& operator=(const SceneBouncingBallGame& sceneBouncingBalls);
	// Member data:
public:
protected:
	Renderer* m_pRenderer;
	std::vector<Ball*> m_pGoodBalls;
	std::vector<Ball*> m_pBadBalls;

	Ball* m_pMeBall;

private:
};
#endif // __SCENEBOUNCINGBALLGAME_H__