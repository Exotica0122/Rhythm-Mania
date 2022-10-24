// COMP710 GP Framework 2022
#ifndef __CIRCLEMANAGER_H__
#define __CIRCLEMANAGER_H__

// Local includes:
#include <vector>
#include "fmod.hpp"

// Forward declarations:
class Renderer;
class Circle;
class InputSystem;
class Score;
class ParticleEmitter;

// Class declaration:
class CircleManager
{
	// Member methods:
public:
	CircleManager();
	~CircleManager();
	void Draw(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	bool Initialise(Renderer& renderer, FMOD::System* soundSystem, Score* score);
	void DebugDraw();
	void LoadCircles(std::vector<std::string> circleData);
	bool UserHitCircle(int x, int y);
	Circle* PeekFirstCircle();
	int GetCircleCount();
	void ResetCircles();
	int GetEndTime();
protected:
private:
	// Member data:
public:
protected:
private:
	FMOD::System* m_pSoundSystem;
	FMOD::Sound* m_pHitSound;
	FMOD::Sound* m_pMissSound;

	Renderer* m_pRenderer;

	ParticleEmitter* m_pParticleEmitter;

	std::vector<Circle*> m_pCircleArray;

	float m_fOffSet;
	float m_fPlayTime;

	int m_iCombo;

	Score* m_pScore;
};
#endif // __CIRCLEMANAGER_H__