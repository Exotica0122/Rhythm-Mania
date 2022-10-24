// COMP710 Peter An

// This include:
#include "scenebouncingballgame.h"

// Local includes:
#include "renderer.h"
#include "ball.h"
#include "imgui/imgui.h"
#include "inputsystem.h"

// Library includes:
#include <cassert>
#include <cstdlib>
#include <math.h> 

SceneBouncingBallGame::SceneBouncingBallGame()
	: m_pMeBall(0)
{
}

SceneBouncingBallGame::~SceneBouncingBallGame()
{
	for (Ball* ball : m_pGoodBalls)
	{
		delete ball;
	}
	m_pGoodBalls.clear();

	for (Ball* ball : m_pBadBalls)
	{
		delete ball;
	}
	m_pBadBalls.clear();

	delete m_pMeBall;
	m_pMeBall = 0;
}

bool
SceneBouncingBallGame::Initialise(Renderer& renderer)
{
	m_pRenderer = &renderer;

	// init good balls
	/*for (int k = 0; k < 10; k++)
	{
		Ball* ball = 0;
		ball = new Ball();
		ball->Initialise(renderer);
		m_pGoodBalls.push_back(ball);
	}*/


	// init me ball
	m_pMeBall = new Ball();
	m_pMeBall->Initialise(renderer);
	m_pMeBall->SetAsPlayer();

	return true;
}

void SceneBouncingBallGame::SpawnGoodBalls(int number)
{
	for (int i = 0; i < number; i++)
	{
		Ball* ball = 0;
		ball = new Ball();
		ball->Initialise(*m_pRenderer, true);
		ball->SetGood();
		m_pGoodBalls.push_back(ball);
	}
}

void SceneBouncingBallGame::SpawnBadBalls(int number)
{
	for (int i = 0; i < number; i++)
	{
		Ball* ball = 0;
		ball = new Ball();
		ball->Initialise(*m_pRenderer, false);
		ball->SetBad();
		m_pBadBalls.push_back(ball);
	}
}

void SceneBouncingBallGame::CheckCollisions()
{
	for (unsigned int i = 0; i < m_pGoodBalls.size(); i++)
	{

		if (m_pGoodBalls[i]->IsAlive() &&BallVsBall(m_pMeBall, m_pGoodBalls[i]))
		{
			m_pGoodBalls[i]->Kill();
			m_pMeBall->Enlarge();
		}
	}

	for (unsigned int j = 0; j < m_pBadBalls.size(); j++)
	{
		if (m_pBadBalls[j]->IsAlive() && BallVsBall(m_pMeBall, m_pBadBalls[j]))
		{
			m_pBadBalls[j]->Kill();
			m_pMeBall->Shrink();
		}
	}
}

bool SceneBouncingBallGame::BallVsBall(Ball* p1, Ball* p2)
{
	float x1 = p1->Position().x;
	float y1 = p1->Position().y;

	float x2 = p2->Position().x;
	float y2 = p2->Position().y;

	float r1 = p1->GetRadius();
	float r2 = p2->GetRadius();

	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) - r1 - r2;

	return (distance <= 0);
}

void
SceneBouncingBallGame::Process(float deltaTime, InputSystem& inputSystem)
{
	m_pMeBall->FollowMouse(inputSystem);

	for (unsigned int k = 0; k < m_pGoodBalls.size(); k++)
	{
		m_pGoodBalls[k]->Process(deltaTime);
	}

	for (unsigned int k = 0; k < m_pBadBalls.size(); k++)
	{
		m_pBadBalls[k]->Process(deltaTime);
	}

	CheckCollisions();
}

void
SceneBouncingBallGame::DebugDraw()
{
	ImGui::Text("Scene: Bouncing Balls");
	m_pMeBall->DebugDraw();
	if (ImGui::Button("Spawn 10 Good"))
	{
		SpawnGoodBalls(10);
	}
	if (ImGui::Button("Spawn 10 Bad"))
	{
		SpawnBadBalls(10);
	}


	//ImGui::Button();
	//ImGui::SliderInt("Show Count", &m_iShowCount, 1, 100);
	//static int editBallNumber = 0;
	//ImGui::SliderInt("Edit ball", &editBallNumber, 0, 99);
	//m_pBalls[editBallNumber]->DebugDraw();
}

void
SceneBouncingBallGame::Draw(Renderer& renderer)
{

	for (unsigned int k = 0; k < m_pGoodBalls.size(); k++)
	{
		m_pGoodBalls[k]->Draw(renderer);
	}

	for (unsigned int k = 0; k < m_pBadBalls.size(); k++)
	{
		m_pBadBalls[k]->Draw(renderer);
	}

	m_pMeBall->Draw(renderer);
}