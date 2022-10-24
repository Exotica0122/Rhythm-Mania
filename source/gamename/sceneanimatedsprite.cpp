// This include:
#include "sceneanimatedsprite.h"

// Local includes:
#include "renderer.h"
#include "animatedsprite.h"
#include "imgui/imgui.h"
#include "inputsystem.h"

// Library includes:
#include <cassert>
#include <cstdlib>

SceneAnimatedSprite::SceneAnimatedSprite()
	: m_pNumberSprite(0)
	, m_pMoreNumberSprite(0)
	, m_pExplosionSprite(0)
{
}

SceneAnimatedSprite::~SceneAnimatedSprite()
{
	delete m_pNumberSprite;
	m_pNumberSprite = 0;

	delete m_pMoreNumberSprite;
	m_pMoreNumberSprite = 0;

	delete m_pExplosionSprite;
	m_pExplosionSprite = 0;
}

bool
SceneAnimatedSprite::Initialise(Renderer& renderer)
{
	m_pNumberSprite = renderer.CreateAnimatedSprite("sprites\\anim8strip.png");
	m_pNumberSprite->SetupFrames(64, 64);
	m_pNumberSprite->SetX(renderer.GetWidth() / 2);
	m_pNumberSprite->SetY(renderer.GetHeight() / 4);
	m_pNumberSprite->Animate();
	m_pNumberSprite->SetFrameDuration(0.1f);
	m_pNumberSprite->SetLooping(true);

	m_pMoreNumberSprite = renderer.CreateAnimatedSprite("sprites\\anim8x2sheet.png");
	m_pMoreNumberSprite->SetupFrames(64, 64);
	m_pMoreNumberSprite->SetX(renderer.GetWidth() / 2);
	m_pMoreNumberSprite->SetY((renderer.GetHeight() / 4) * 2);
	m_pMoreNumberSprite->Animate();
	m_pMoreNumberSprite->SetFrameDuration(0.1f);
	m_pMoreNumberSprite->SetLooping(true);

	m_pExplosionSprite = renderer.CreateAnimatedSprite("sprites\\explosion.png");
	m_pExplosionSprite->SetupFrames(64, 64);
	m_pExplosionSprite->SetX(renderer.GetWidth() / 2);
	m_pExplosionSprite->SetY((renderer.GetHeight() / 4) * 3);
	m_pExplosionSprite->Animate();
	m_pExplosionSprite->SetFrameDuration(0.1f);
	m_pExplosionSprite->SetLooping(true);

	return true;
}

void
SceneAnimatedSprite::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pNumberSprite->Process(deltaTime);
	m_pMoreNumberSprite->Process(deltaTime);
	m_pExplosionSprite->Process(deltaTime);
}

void
SceneAnimatedSprite::DebugDraw()
{
	m_pNumberSprite->DebugDraw();
	m_pMoreNumberSprite->DebugDraw();
	m_pExplosionSprite->DebugDraw();
}

void
SceneAnimatedSprite::Draw(Renderer& renderer)
{
	m_pNumberSprite->Draw(renderer);
	m_pMoreNumberSprite->Draw(renderer);
	m_pExplosionSprite->Draw(renderer);
}