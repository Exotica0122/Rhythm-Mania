// COMP710 Peter An

// This include:
#include "sceneinstructions.h"

#include "inputsystem.h"
#include "renderer.h"
#include "sprite.h"

SceneInstructions::SceneInstructions()
{

}

SceneInstructions::~SceneInstructions()
{
	delete m_pInstructions;
	m_pInstructions = 0;
}

bool
SceneInstructions::Initialise(Renderer& renderer, FMOD::System* soundSystem)
{
	m_pInstructions = renderer.CreateSprite("sprites\\Instructions.png");
	m_pInstructions->SetX(renderer.GetWidth() / 2);
	m_pInstructions->SetY(renderer.GetHeight() / 2);

	return true;
}

bool
SceneInstructions::GetIsPaused()
{
	return true;
}

void
SceneInstructions::Process(float deltaTime, InputSystem& inputSystem)
{

}

void
SceneInstructions::Draw(Renderer& renderer)
{
	m_pInstructions->Draw(renderer);
}

void 
SceneInstructions::DebugDraw()
{

}