// COMP710 GP Framework 2022
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "fmod.hpp"

// Forward declarations:
class Renderer;
class Sprite;
class Scene;
class InputSystem;

class Game
{
    // Member methods:
public:
    static Game& GetInstance();
    static void DestroyInstance();

    bool Initialise();
	void ToggleDebugWindow();
    bool DoGameLoop();
    void Quit();

protected:
    void Process(float deltaTime);
	void DebugDraw();
    void Draw(Renderer& renderer);

    void ProcessFrameCounting(float deltaTime);

private:
    Game();
    ~Game();
    Game(const Game& game);
    Game& operator=(const Game& game);

    // Member data:
public:

protected:
    static Game* sm_pInstance;
    Renderer* m_pRenderer;

    __int64 m_iLastTime;
    float m_fExecutionTime;
    float m_fElapsedSeconds;
    int m_iFrameCount;
    int m_iFPS;

	FMOD::System* m_pFMODSystem;
	FMOD::Sound* m_pHitSound;

	std::vector<Scene*> m_scenes;
	int m_iCurrentScene;

#ifdef USE_LAG
    float m_fLag;
    int m_iUpdateCount;
#endif // USE_LAG

    bool m_bLooping;
	bool m_bPauseSimulation;

	InputSystem* m_pInputSystem;
	bool m_bShowDebugWindow;

private:

};

#endif // __GAME_H__
