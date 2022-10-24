// COMP710 Peter An

// This include:
#include "circlemanager.h"

#include "circle.h"
#include "inputsystem.h"
#include "logmanager.h"
#include "renderer.h"
#include "score.h"
#include "particleemitter.h"
#include "imgui/imgui.h"
#include "sprite.h"

CircleManager::CircleManager()
	: m_fOffSet(0)
	, m_fPlayTime(0)
	, m_iCombo(0)
{

}

CircleManager::~CircleManager()
{
	for (Circle* circle : m_pCircleArray)
	{
		delete circle;
	}
	m_pCircleArray.clear();

	delete m_pParticleEmitter;
	m_pParticleEmitter = 0;
}

void
CircleManager::LoadCircles(std::vector<std::string> circleData)
{
	for (std::string circleString : circleData)
	{
		char* c = const_cast<char*>(circleString.c_str());
		c = strtok(c, ",");
		int x = atoi(c);
		c = strtok(NULL, ",");
		int y = atoi(c);
		c = strtok(NULL, ",");
		float time = atof(c);

		Circle* circle = new Circle();
		circle->Initialise(*m_pRenderer, m_pSoundSystem, m_pHitSound, m_pMissSound);
		circle->SetPosition(static_cast<int>((x * 2) + ((m_pRenderer->GetWidth() / 2) - 516)), static_cast<int>((y * 2) + 82));
		circle->SetHitTime((time + m_fOffSet) / 1000);
		m_pCircleArray.push_back(circle);
	}
}

bool
CircleManager::Initialise(Renderer& renderer, FMOD::System* soundSystem, Score* score)
{
	m_pParticleEmitter = new ParticleEmitter();
	m_pParticleEmitter->SetSharedSprite(renderer.CreateSprite("sprites\\particle300@2x.png"));
	m_pParticleEmitter->Initialise(renderer);
	m_pParticleEmitter->SetBatchSize(0);
	m_pParticleEmitter->SetAccelerationScalar(10.f);
	m_pParticleEmitter->SetParticleLifeSpan(0.5f);

	m_pRenderer = &renderer;
	m_pSoundSystem = soundSystem;
	m_pScore = score;

	soundSystem->createSound("skins\\Exotica1.2\\normal-hitwhistle.wav", FMOD_DEFAULT, 0, &m_pHitSound);
	soundSystem->createSound("skins\\Exotica1.2\\combobreak.mp3", FMOD_DEFAULT, 0, &m_pMissSound);

	return true;
}

void
CircleManager::Process(float deltaTime, InputSystem& inputSystem)
{
	if (deltaTime <= 0)
	{
		return;
	}

	m_fPlayTime += deltaTime;

	bool firstCircleHit = false;
	for (Circle* circle : m_pCircleArray)
	{
		circle->Process(deltaTime, inputSystem);
		if (!circle->IsAlive()) continue;
		if (inputSystem.GetMouseButtonState(SDL_BUTTON_LEFT) == BS_PRESSED ||
			inputSystem.GetMouseButtonState(SDL_BUTTON_RIGHT) == BS_PRESSED ||
			inputSystem.GetKeyState(SDL_SCANCODE_COMMA) == BS_PRESSED ||
			inputSystem.GetKeyState(SDL_SCANCODE_PERIOD) == BS_PRESSED)
		{
			if (circle->CircleHit(inputSystem) && !firstCircleHit)
			{
				m_pParticleEmitter->SetPosition(inputSystem.GetMousePosition().x, inputSystem.GetMousePosition().y);
				for (int i = 0; i < 10; i++) 
				{
					m_pParticleEmitter->Spawn();
				}
				circle->RegisterHit(m_fPlayTime);
				m_iCombo++;
				m_pScore->AddScore(300);
			}
		}
		firstCircleHit = true;
	}

	m_pParticleEmitter->Process(deltaTime);
	// TODO: COMBO
}

bool
CircleManager::UserHitCircle(int x, int y)
{
	return false;
}

Circle*
CircleManager::PeekFirstCircle()
{
	return m_pCircleArray.at(0);
}

int
CircleManager::GetCircleCount()
{
	return m_pCircleArray.size();
}

void  
CircleManager::ResetCircles()
{
	m_fPlayTime = 0.f;
	for (int k = m_pCircleArray.size() - 1; k >= 0; k--)
	{
		m_pCircleArray[k]->Reset();
	}
}

void
CircleManager::Draw(Renderer& renderer)
{
	for (int k = m_pCircleArray.size() - 1; k >= 0; k--)
	{
		m_pCircleArray[k]->Draw(renderer);
	}
	m_pParticleEmitter->Draw(renderer);
}

int 
CircleManager::GetEndTime()
{
	return m_pCircleArray[m_pCircleArray.size() - 1]->GetHitTime() + 1;
}

void
CircleManager::DebugDraw()
{
	ImGui::Text("Score (%d)", m_pScore->GetCurrentScore());
	/*ImGui::Text("Percentage (%f)", m_pScore->GetScorePercentage());*/
	ImGui::Text("Combo (%d)", m_iCombo);
}

