// COMP710 GP Framework 2022
#ifndef __SCENEPARTICLESYSTEM_H__
#define __SCENEPARTICLESYSTEM_H__

// Local includes:
#include "scene.h"

// Forward declarations:
class Renderer;
class Ball;
class ParticleEmitter;

// Class declaration:
class SceneParticleSystem : public Scene
{
	// Member methods:
public:
	SceneParticleSystem();
	virtual ~SceneParticleSystem();
	virtual bool Initialise(Renderer& renderer);
	virtual void Process(float deltaTime, InputSystem& inputSystem);
	virtual void DebugDraw();
	virtual void Draw(Renderer& renderer);
protected:
private:
	SceneParticleSystem(const SceneParticleSystem& sceneBouncingBalls);
	SceneParticleSystem& operator=(const SceneParticleSystem& sceneBouncingBalls);
	// Member data:
public:
protected:
	ParticleEmitter* m_pParticleEmitter;
private:
};

#endif // __SCENEPARTICLESYSTEM_H__