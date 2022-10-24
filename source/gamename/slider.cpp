// COMP710 GP Framework 2022

// This include:
#include "slider.h"

// Local includes:
#include "renderer.h"
#include "sprite.h"
#include "inputsystem.h"
#include "inlinehelper.h"
#include "imgui/imgui.h"

// Library includes:
#include <cassert>
#include <cstdlib>
#include <stdio.h>

// Static members:
float Slider::sm_fBoundaryWidth = 0.0f;
float Slider::sm_fBoundaryHeight = 0.0f;


Slider::Slider()
	: m_pHitCircle(0)
	, m_pCircleOverlay(0)
	, m_pApproachCircle(0)
{
}
Slider::~Slider()
{
	delete m_pHitCircle;
	m_pHitCircle = 0;

	delete m_pCircleOverlay;
	m_pCircleOverlay = 0;

	delete m_pApproachCircle;
	m_pApproachCircle = 0;
}

bool
Slider::Initialise(Renderer& renderer)
{
	m_fPlayTime = 0;
	m_fHitAtHit = 0;

	m_pHitCircle = renderer.CreateSprite("skins\\Exotica1.2\\hitcircle.png");
	m_pCircleOverlay = renderer.CreateSprite("skins\\Exotica1.2\\hitcircleoverlay.png");
	m_pApproachCircle = renderer.CreateSprite("skins\\Exotica1.2\\approachcircle.png");
	m_pApproachCircle->SetScale(2);

	m_bAlive = false;


	const float MAX_SPEED = 250.0f;
	const int EDGE_LIMIT = m_pHitCircle->GetWidth();
	const int SCREEN_WIDTH = renderer.GetWidth();
	const int SCREEN_HEIGHT = renderer.GetHeight();
	//sm_fBoundaryWidth = static_cast<float>(SCREEN_WIDTH);
	//sm_fBoundaryHeight = static_cast<float>(SCREEN_HEIGHT);
	m_position.x = static_cast<float>(GetRandom(EDGE_LIMIT, SCREEN_WIDTH - EDGE_LIMIT));
	m_position.y = static_cast<float>(GetRandom(EDGE_LIMIT, SCREEN_HEIGHT - EDGE_LIMIT));
	m_velocity.x = GetRandomPercentage() * MAX_SPEED * GetPositiveOrNegative();
	m_velocity.y = GetRandomPercentage() * MAX_SPEED * GetPositiveOrNegative();
	ComputeBounds(SCREEN_WIDTH, SCREEN_HEIGHT);

	m_pHitCircle->SetX(SCREEN_WIDTH / 2);
	m_pHitCircle->SetY(SCREEN_HEIGHT / 2);

	m_pCircleOverlay->SetX(SCREEN_WIDTH / 2);
	m_pCircleOverlay->SetY(SCREEN_HEIGHT / 2);

	m_pApproachCircle->SetX(SCREEN_WIDTH / 2);
	m_pApproachCircle->SetY(SCREEN_HEIGHT / 2);

	return true;
}

void
Slider::Process(float deltaTime, InputSystem& inputSystem)
{
	m_fPlayTime += deltaTime;

	if (m_fPlayTime + 1 > m_fHitTime)
	{
		if (m_fHitAtHit == 0)
		{
			m_bAlive = true;
		}
		float newScale = m_pApproachCircle->GetScale() - 0.001f;
		if (newScale > 1)
		{
			m_pApproachCircle->SetScale(newScale);
		}
	}


	if (m_fPlayTime > m_fHitTime)
	{
		printf("Missed!");
		m_bAlive = false;
	}

	if (m_bAlive && inputSystem.GetMouseButtonState(1))
	{
		if (CircleHit(inputSystem))
		{
			m_fHitAtHit = m_fPlayTime;
			m_bAlive = false;
			printf("You hit the circle!");
		}
	}
}

void
Slider::DebugDraw()
{
	ImGui::InputFloat2("Position", reinterpret_cast<float*>(&m_position));
	ImGui::InputFloat2("Velocity", reinterpret_cast<float*>(&m_velocity));
	ImGui::Text("Size (%d, %d)", m_pHitCircle->GetWidth(), m_pHitCircle->GetHeight());
	ImGui::Text("Lowerbound (%f, %f)", m_boundaryLow.x, m_boundaryLow.y);
	ImGui::Text("Upperbound (%f, %f)", m_boundaryHigh.x, m_boundaryHigh.y);
	float spriteScale = m_pHitCircle->GetScale();
	ImGui::InputFloat("Scale", &spriteScale, 0.05f);
	m_pHitCircle->SetScale(spriteScale);
	ComputeBounds(static_cast<int>(sm_fBoundaryWidth), static_cast<int>(sm_fBoundaryHeight));
	float colour[4];
	colour[0] = m_pHitCircle->GetRedTint();
	colour[1] = m_pHitCircle->GetGreenTint();
	colour[2] = m_pHitCircle->GetBlueTint();
	colour[3] = m_pHitCircle->GetAlpha();
	ImGui::ColorEdit4("Ball colour", colour);
	m_pHitCircle->SetRedTint(colour[0]);
	m_pHitCircle->SetGreenTint(colour[1]);
	m_pHitCircle->SetBlueTint(colour[2]);
	m_pHitCircle->SetAlpha(colour[3]);

	ImGui::Text("Play Time (%f)", m_fPlayTime);
}

void
Slider::Draw(Renderer& renderer)
{
	if (m_bAlive)
	{
		m_pHitCircle->Draw(renderer);
		m_pCircleOverlay->Draw(renderer);
		m_pApproachCircle->Draw(renderer);
	}
}

Vector2&
Slider::Position()
{
	return m_position;
}

void
Slider::ComputeBounds(int width, int height)
{
	m_boundaryLow.x = (m_pHitCircle->GetWidth() / 2.0f);
	m_boundaryLow.y = (m_pHitCircle->GetHeight() / 2.0f);
	m_boundaryHigh.x = width - (m_pHitCircle->GetWidth() / 2.0f);
	m_boundaryHigh.y = height - (m_pHitCircle->GetHeight() / 2.0f);
}

float
Slider::GetRadius()
{
	float radius = m_pHitCircle->GetWidth() / 2;
	return radius;
}

void
Slider::SetHitTime(float hitTime)
{
	m_fHitTime = hitTime;
}

void
Slider::SetSliderPoints(std::vector<Vector2*> sliderPonits)
{
	m_pSliderPoints = sliderPonits;
}

bool
Slider::CircleHit(InputSystem& inputSystem)
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