// COMP710 GP Framework 2022
#ifndef __SLIDER_H__
#define __SLIDER_H__

#include <vector>

// Local includes:
#include "vector2.h"

// Forward declarations:
class Renderer;
class Sprite;
class InputSystem;

// Class declaration:
class Slider
{
	// Member methods:
public:
	Slider();
	~Slider();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void DebugDraw();
	void Draw(Renderer& renderer);
	Vector2& Position();
	void SetHitTime(float hitTime);
	void SetSliderPoints(std::vector<Vector2*> sliderPonits);

	float GetRadius();
protected:
	void ComputeBounds(int width, int height);
	bool CircleHit(InputSystem& inputSystem);
private:
	Slider(const Slider& circle);
	Slider& operator=(const Slider& circle);
	// Member data:
public:
protected:
	Vector2 m_position;
	std::vector<Vector2*> m_pSliderPoints;
	Vector2 m_velocity;
	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	Sprite* m_pHitCircle;
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
#endif // __SLIDER_H__