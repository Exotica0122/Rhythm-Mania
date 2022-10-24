// COMP710 GP Framework 
#ifndef __SCENEINSTRUCTIONS_H__ 
#define __SCENEINSTRUCTIONS_H__ 

// local includes: 
#include "scene.h"

#include "fmod.hpp"

// Forward declarations:  
class Renderer;
class InputSystem;
class Sprite;

// Class declaration:  
class SceneInstructions : public Scene
{
	// Member methods:  
public:
	SceneInstructions();
	virtual ~SceneInstructions();
	virtual bool Initialise(Renderer& renderer, FMOD::System* soundSystem);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void Draw(Renderer& renderer);
	virtual bool GetIsPaused();

protected:

private:
	SceneInstructions(const SceneInstructions& sceneInstructions);
	SceneInstructions& operator=(const SceneInstructions& sceneInstructions);

	// Member data:  
public:

protected:

private:
	Sprite* m_pInstructions;
};

#endif // __SCENEINSTRUCTIONS_H__ 