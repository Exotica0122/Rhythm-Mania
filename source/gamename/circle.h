// COMP710 GP Framework 2022
#ifndef __CIRCLE_H__
#define __CIRCLE_H__

// Local includes:
#include "vector2.h"
#include "fmod.hpp"

// Forward declarations:
class Renderer;
class Sprite;
class InputSystem;


// Class declaration:
class Circle
{
	// Member methods:
public:
	Circle();
	~Circle();
	bool Initialise(Renderer& renderer, FMOD::System* soundSystem, FMOD::Sound* hitSound, FMOD::Sound* missSound);
	void Process(float deltaTime, InputSystem& inputSystem);
	void DebugDraw();
	void Draw(Renderer& renderer);
	Vector2& Position();
	void SetHitTime(float hitTime);
	void SetPosition(int x, int y);
	bool CircleHit(InputSystem& inputSystem);
	void RegisterHit(float time);
	bool IsAlive();

	float GetRadius();
	float GetHitTime();
	void Reset();
protected:
	void PlayHitSound();
	void PlayMissSound();
private:
	Circle(const Circle& circle);
	Circle& operator=(const Circle& circle);
	// Member data:
public:
protected:
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	Sprite* m_pHitCircle;
	Sprite* m_pCircleOverlay;
	Sprite* m_pApproachCircle;
	bool m_bAlive;
	float m_fHitAtHit;
	float m_fHitTime;

	FMOD::System* m_pSystemSound;
	FMOD::Sound* m_pHitSound;
	FMOD::Sound* m_pMissSound;

	float m_fPlayTime;
private:
};
#endif // __CIRCLE_H__