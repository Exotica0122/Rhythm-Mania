// This include:
#include "sceneparticlesystem.h"

// Local includes:
#include "renderer.h"
#include "particleemitter.h"
#include "imgui/imgui.h"

// Library includes:
#include <cassert>
#include <cstdlib>

SceneParticleSystem::SceneParticleSystem()
	: m_pParticleEmitter(0)
{

}

SceneParticleSystem::~SceneParticleSystem()
{
	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}

bool
SceneParticleSystem::Initialise(Renderer& renderer)
{
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->Initialise(renderer);

	return true;
}

void
SceneParticleSystem::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pParticleEmitter->Process(deltaTime);
}

void
SceneParticleSystem::DebugDraw()
{
	// Draw Imgui for particle system
	m_pParticleEmitter->DebugDraw();
}

void
SceneParticleSystem::Draw(Renderer& renderer)
{
	m_pParticleEmitter->Draw(renderer);
}