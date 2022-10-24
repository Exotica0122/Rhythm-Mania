// COMP710 GP Framework 
#ifndef __MAINSCREEN_H__ 
#define __MAINSCREEN_H__ 

// local includes: 
#include "scene.h"

// Forward declarations:  
class Renderer;
class InputSystem;
class Sprite;

// Class declaration:  
class MainScreen : public Scene
{
	// Member methods:  
public:
	MainScreen();
	virtual ~MainScreen();
	virtual bool Initialise(Renderer& renderer, FMOD::System* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void Draw(Renderer& renderer);
	virtual bool GetIsPaused();

protected:

private:
	MainScreen(const MainScreen& mainScreen);
	MainScreen& operator=(const MainScreen& mainScreen);

	// Member data:  
public:

protected:

private:
	Sprite* m_pMainScreen;
	Sprite* m_pMainScreenText;
};

#endif // __MAINSCREEN_H__ 