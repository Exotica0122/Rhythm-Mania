// COMP710 GP Framework 2022

// This include:
#include "circle.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"
#include "logmanager.h"

// Library includes:
#include <cassert>
#include <cstdlib>
#include <stdio.h>
#include "fmod.hpp"

Circle::Circle()
	: m_pHitCircle(0)
	, m_pCircleOverlay(0)
	, m_pApproachCircle(0)
{
}
Circle::~Circle()
{
	delete m_pHitCircle;
	m_pHitCircle = 0;

	delete m_pCircleOverlay;
	m_pCircleOverlay = 0;

	delete m_pApproachCircle;
	m_pApproachCircle = 0;
}

bool
Circle::Initialise(Renderer& renderer, FMOD::System* soundSystem, FMOD::Sound* hitSound, FMOD::Sound* missSound)
{
	m_fPlayTime = 0;
	m_fHitAtHit = 0;

	m_pHitCircle = renderer.CreateSprite("skins\\Exotica1.2\\hitcircle.png");
	m_pCircleOverlay = renderer.CreateSprite("skins\\Exotica1.2\\hitcircleoverlay.png");
	m_pApproachCircle = renderer.CreateSprite("skins\\Exotica1.2\\approachcircle.png");
	m_pApproachCircle->SetScale(2);

	m_bAlive = false;

	m_pSystemSound = soundSystem;
	m_pHitSound = hitSound;
	m_pMissSound = missSound;

	return true;
}

void
Circle::Process(float deltaTime, InputSystem& inputSystem)
{
	m_fPlayTime += deltaTime;

	// Handle spawn
	if (m_fPlayTime > m_fHitTime - 0.4 && m_fPlayTime < m_fHitTime + 0.2)
	{
		if (!m_bAlive && m_fHitAtHit == 0)
		{
			m_bAlive = true;
		}
		float newScale = Lerp(1, 4, m_fHitTime - m_fPlayTime);
		float newAlpha = Lerp(1, 0, m_fHitTime - m_fPlayTime);
		if (newScale > 1)
		{
			m_pApproachCircle->SetScale(newScale);
			m_pApproachCircle->SetAlpha(newAlpha);
		}
		else
		{
			m_pApproachCircle->SetAlpha(0);
		}
		return;
	}

	// Handle miss
	if (m_bAlive && m_fHitAtHit == 0)
	{
		PlayMissSound();
	}

	m_bAlive = false;
}

void
Circle::DebugDraw()
{
}

void
Circle::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pHitCircle->Draw(renderer);
		m_pCircleOverlay->Draw(renderer);
		m_pApproachCircle->Draw(renderer);
	}
}

Vector2&
Circle::Position()
{
	return m_position;
}

float
Circle::GetRadius()
{
	float radius = m_pHitCircle->GetWidth() / 2;
	return radius;
}

float 
Circle::GetHitTime()
{
	return m_fHitTime;
}

void
Circle::SetHitTime(float hitTime)
{
	m_fHitTime = hitTime;
}

void
Circle::SetPosition(int x, int y)
{
	m_position.Set(x, y);

	m_pHitCircle->SetX(x);
	m_pHitCircle->SetY(y);

	m_pCircleOverlay->SetX(x);
	m_pCircleOverlay->SetY(y);

	m_pApproachCircle->SetX(x);
	m_pApproachCircle->SetY(y);
}

bool
Circle::CircleHit(InputSystem& inputSystem)
{
	float x1 = m_pHitCircle->GetX();
	float y1 = m_pHitCircle->GetY();

	float x2 = inputSystem.GetMousePosition().x;
	float y2 = inputSystem.GetMousePosition().y;

	float r1 = m_pHitCircle->GetWidth() / 2;
	float r2 = 1;

	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) - r1 - r2;

	return (distance <= 0);
}

bool
Circle::IsAlive()
{
	return m_bAlive;
}

void
Circle::PlayHitSound()
{
	m_pSystemSound->playSound(m_pHitSound, 0, false, 0);
}

void
Circle::PlayMissSound()
{
	m_pSystemSound->playSound(m_pMissSound, 0, false, 0);
}

void
Circle::RegisterHit(float time)
{
	PlayHitSound();
	m_bAlive = false;
	m_fHitAtHit = time;
}

void 
Circle::Reset()
{
	m_bAlive = false;
	m_fHitAtHit = 0.f;
	m_fPlayTime = 0.f;
}