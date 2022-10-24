// COMP710 GP Framework 2022
#ifndef __SPINNER_H__
#define __SPINNER_H__

// Local includes:
#include "vector2.h"

// Forward declarations:
class Renderer;
class Sprite;
class InputSystem;

// Class declaration:
class Spinner
{
	// Member methods:
public:
	Spinner();
	~Spinner();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void DebugDraw();
	void Draw(Renderer& renderer);
	Vector2& Position();
	void SetHitTime(float hitTime);
	//void SetSliderPoints(std::vector<Vector2*> sliderPonits);

	float GetRadius();
protected:
	bool CircleHit(InputSystem& inputSystem);
private:
	Spinner(const Spinner& circle);
	Spinner& operator=(const Spinner& circle);
	// Member data:
public:
protected:
	Vector2 m_position;
	Vector2 m_velocity;

	Sprite* m_pSpinner;
	Sprite* m_pCircleOverlay;
	Sprite* m_pApproachCircle;

	bool m_bAlive;
	float m_fHitAtHit;
	float m_fHitTime;

	float m_fPlayTime;
	static float sm_fBoundaryWidth;
	static float sm_fBoundaryHeight;
private:
};
#endif // __SPINNER_H__