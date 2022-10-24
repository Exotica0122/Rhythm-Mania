// COMP710 GP Framework 2022
#ifndef __SCENESPLASHSCREENAUT_H__
#define __SCENESPLASHSCREENAUT_H__


// Local includes:
#include "scene.h"

// Forward declarations: 
class Renderer;
class Sprite;


// Class declaration: 


class SceneSplashScreen : public Scene
{
	// Member methods: 
public:
	SceneSplashScreen();
	virtual ~SceneSplashScreen();
	virtual bool Initialise(Renderer& renderer, FMOD::System* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void Draw(Renderer& renderer);
	virtual bool GetIsPaused();

protected:
private:
	SceneSplashScreen(const SceneSplashScreen& sceneCheckerboards);
	SceneSplashScreen& operator=(const SceneSplashScreen& sceneCheckerboards);

	// Member data: 
public:
protected:
	Sprite* m_pSplashScreen;

	float m_fCurrentTime;
private:

	
};

#endif // __SCENESPLASHSCREENAUT_H__