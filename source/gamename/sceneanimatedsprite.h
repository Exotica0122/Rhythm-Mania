// COMP710 GP Framework 2022
#ifndef __SCENEANIMATEDSPRITE_H__
#define __SCENEANIMATEDSPRITE_H__

// Local includes:
#include "scene.h"

// Forward declarations:
class Renderer;
class Ball;
class AnimatedSprite;

// Class declaration:
class SceneAnimatedSprite : public Scene
{
	// Member methods:
public:
	SceneAnimatedSprite();
	virtual ~SceneAnimatedSprite();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void Draw(Renderer& renderer);
protected:
private:
	SceneAnimatedSprite(const SceneAnimatedSprite& sceneBouncingBalls);
	SceneAnimatedSprite& operator=(const SceneAnimatedSprite& sceneBouncingBalls);
	// Member data:
public:
protected:
	AnimatedSprite* m_pNumberSprite;
	AnimatedSprite* m_pMoreNumberSprite;
	AnimatedSprite* m_pExplosionSprite;
private:
};

#endif // __SCENEANIMATEDSPRITE_H__a