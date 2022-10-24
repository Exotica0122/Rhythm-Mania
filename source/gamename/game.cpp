// COMP710 GP Framework 2022

#include <stdlib.h>

// This include:
#include "game.h"

// Library includes:
#include "renderer.h"
#include "logmanager.h"
#include "sprite.h"
#include "scene.h"
#include "scenesplashscreen.h"
#include "mainscreen.h"
#include "scenecanondeasy.h"
#include "scenecanondinsane.h"
#include "scenecanondhard.h"
#include "sceneinstructions.h"

#include "imgui/imgui_impl_sdl.h"
#include "inputsystem.h"
#include "xboxcontroller.h"

#include "fmod.hpp"
#include "fmod_errors.h"

// Static Members:
Game* Game::sm_pInstance = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pRenderer(0)
	, m_bLooping(true)
	, m_bShowDebugWindow(false)
	, m_fElapsedSeconds(0.f)
	, m_fExecutionTime(0.f)
{

}

Game::~Game()
{
	delete m_pRenderer;
	m_pRenderer = 0;

	for (Scene* scene : m_scenes)
	{
		delete scene;
	}
	m_scenes.clear();

	delete m_pInputSystem;
	m_pInputSystem = 0;

}

void
Game::Quit()
{
	m_bLooping = false;
}

bool
Game::Initialise()
{
	int bbWidth = 1280;
	int bbHeight = 960;

	m_pRenderer = new Renderer();
	if (!m_pRenderer->Initialise(false, bbWidth, bbHeight))
	{
		LogManager::GetInstance().Log("Renderer failed to initialise!");
		return false;
	}

	bbWidth = m_pRenderer->GetWidth();
	bbHeight = m_pRenderer->GetHeight();

	m_iLastTime = SDL_GetPerformanceCounter();

	m_pRenderer->SetClearColour(0, 0, 0);

	m_pInputSystem = new InputSystem();
	m_pInputSystem->Initialise();

	m_bPauseSimulation = false;

	//FMOD
	FMOD::System_Create(&m_pFMODSystem);
	m_pFMODSystem->init(512, FMOD_INIT_NORMAL, 0);

	Scene* pSplashScreen = 0;
	pSplashScreen = new SceneSplashScreen();
	pSplashScreen->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pSplashScreen);

	Scene* pMainScreen = 0;
	pMainScreen = new MainScreen();
	pMainScreen->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pMainScreen);

	Scene* pSceneCanonDEasy = 0;
	pSceneCanonDEasy = new SceneCanonDEasy();
	pSceneCanonDEasy->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pSceneCanonDEasy);

	Scene* pSceneCanonDHard = 0;
	pSceneCanonDHard = new SceneCanonDHard();
	pSceneCanonDHard->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pSceneCanonDHard);

	Scene* pSceneCanonDInsane = 0;
	pSceneCanonDInsane = new SceneCanonDInsane();
	pSceneCanonDInsane->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pSceneCanonDInsane);

	Scene* pSceneInstructions = 0;
	pSceneInstructions = new SceneInstructions();
	pSceneInstructions->Initialise(*m_pRenderer, m_pFMODSystem);
	m_scenes.push_back(pSceneInstructions);

	m_iCurrentScene = 0;

	return true;
}

void
Game::ToggleDebugWindow()
{
	m_bShowDebugWindow = !m_bShowDebugWindow;
	m_pInputSystem->ShowMouseCursor(m_bShowDebugWindow);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	m_pInputSystem->ProcessInput();

	SDL_Event event;
	while (SDL_PollEvent(&event) != 0)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplSDL2_ProcessEvent(&event);

		if (event.type == SDL_QUIT)
		{
			Quit();
		}
	}

	if (m_bLooping)
	{
		Uint64 current = SDL_GetPerformanceCounter();
		float deltaTime = (current - m_iLastTime) / static_cast<float>(SDL_GetPerformanceFrequency());

		m_iLastTime = current;

		m_fExecutionTime += deltaTime;

		Process(deltaTime);

#ifdef USE_LAG
		m_fLag += deltaTime;

		int innerLag = 0;

		while (m_fLag >= stepSize)
		{
			Process(stepSize);

			m_fLag -= stepSize;

			++m_iUpdateCount;
			++innerLag;
		}
#endif //USE_LAG

		Draw(*m_pRenderer);
	}

	return m_bLooping;
}

void
Game::Process(float deltaTime)
{
	if (m_bPauseSimulation)
	{
		deltaTime = 0.0f;
	}

	ProcessFrameCounting(deltaTime);

	//m_scenes[m_iCurrentScene]->Process(deltaTime);
	m_scenes[m_iCurrentScene]->Process(deltaTime, *m_pInputSystem);

	if (m_fExecutionTime > 6.f && m_fExecutionTime < 6.1f)
	{
		m_iCurrentScene = 1;
	}

	if (m_pInputSystem->GetKeyState(SDL_SCANCODE_F2) == BS_PRESSED)
	{
		ToggleDebugWindow();
	}

	if (m_iCurrentScene == 1)
	{
		if (m_pInputSystem->GetKeyState(SDL_SCANCODE_ESCAPE) == BS_PRESSED)
		{
			Quit();
		}
		// Easy
		if (m_pInputSystem->GetKeyState(SDL_SCANCODE_1) == BS_PRESSED)
		{
			m_iCurrentScene = 2;
		}
		// Hard
		if (m_pInputSystem->GetKeyState(SDL_SCANCODE_2) == BS_PRESSED)
		{
			m_iCurrentScene = 3;
		}
		 //Insane
		if (m_pInputSystem->GetKeyState(SDL_SCANCODE_3) == BS_PRESSED)
		{
			m_iCurrentScene = 4;
		}
		// Instructions
		if (m_pInputSystem->GetKeyState(SDL_SCANCODE_0) == BS_PRESSED)
		{
			m_iCurrentScene = 5;
		}
	}


	if (m_iCurrentScene != 1 && m_pInputSystem->GetKeyState(SDL_SCANCODE_BACKSPACE) == BS_PRESSED &&
		m_scenes[m_iCurrentScene]->GetIsPaused())
	{
		m_iCurrentScene = 1;
	}

	m_pFMODSystem->update();
}

void
Game::DebugDraw()
{
	if (m_bShowDebugWindow)
	{
		bool open = true;
		ImGui::Begin("Debug Window", &open, ImGuiWindowFlags_MenuBar);
		ImGui::Text("COMP710 GP Framework (%s)", "2022, S2");
		ImGui::Text("FPS: (%d)", m_iFPS);
		ImGui::Text("Elapsed Seconds: (%f)", m_fExecutionTime);
		if (ImGui::Button("Quit"))
		{
			Quit();
		}
		if (ImGui::Button("Pause simulation"))
		{
			m_bPauseSimulation = !m_bPauseSimulation;
		}
		ImGui::SliderInt("Active scene", &m_iCurrentScene, 0, m_scenes.size() - 1, "%d");
		m_scenes[m_iCurrentScene]->DebugDraw();		
		ImGui::End();

		ImGui::Begin("Texture Window", &open, ImGuiWindowFlags_MenuBar);
		ImGui::Separator();
		m_pRenderer->DebugDraw();
		ImGui::End();

		ImGui::Begin("Log Window", &open, ImGuiWindowFlags_MenuBar);
		ImGui::Text("Log Manager");
		LogManager::GetInstance().DebugDraw();
		ImGui::End();
	}
}

void
Game::Draw(Renderer& renderer)
{
	++m_iFrameCount;

	renderer.Clear();

	m_scenes[m_iCurrentScene]->Draw(renderer);

	DebugDraw();

	renderer.Present();
}

void
Game::ProcessFrameCounting(float deltaTime)
{
	// Count total simulation time elapsed:
	m_fElapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_fElapsedSeconds > 1.0f)
	{
		m_fElapsedSeconds -= 1.0f;
		m_iFPS = m_iFrameCount;
		m_iFrameCount = 0;
	}
}
