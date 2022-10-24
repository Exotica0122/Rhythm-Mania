// COMP710 GP Framework 2022

// This include:
#include "cursor.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "particleemitter.h"
#include "xboxcontroller.h"

// Library includes:
#include <cassert>
#include <cstdlib>


Cursor::Cursor()
	: m_pSprite(0)
	, m_deadZoneX(2500)
	, m_deadZoneY(2500)
{
}
Cursor::~Cursor()
{
	delete m_pSprite;
	m_pSprite = 0;

	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}

bool
Cursor::Initialise(Renderer& renderer)
{
	m_pSprite = renderer.CreateSprite("skins\\Exotica1.2\\cursor.png");
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->SetSharedSprite(renderer.CreateSprite("sprites\\star2.png"));
	m_pParticleEmitter->Initialise(renderer);
	m_pParticleEmitter->SetEmissionRate(0.4f);

	return true;
}

void
Cursor::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pSprite->Process(deltaTime);
	m_pParticleEmitter->Process(deltaTime);

	m_position += m_velocity * deltaTime;
}

void
Cursor::FollowMouse(InputSystem& inputSystem)
{
	m_pParticleEmitter->SetPosition(inputSystem.GetMousePosition().x, inputSystem.GetMousePosition().y);
	m_position.Set(inputSystem.GetMousePosition().x, inputSystem.GetMousePosition().y);

	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));
}

void
Cursor::DebugDraw()
{
	m_pParticleEmitter->DebugDraw();
}

void
Cursor::Draw(Renderer& renderer)
{
	m_pParticleEmitter->Draw(renderer);
	m_pSprite->Draw(renderer);
}

Vector2&
Cursor::Position()
{
	return m_position;
}

float
Cursor::GetRadius()
{
	float radius = m_pSprite->GetWidth() / 2;
	return radius;
}