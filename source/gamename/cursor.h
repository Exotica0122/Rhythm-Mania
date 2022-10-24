// COMP710 GP Framework 2022
#ifndef __CURSOR_H__
#define __CURSOR_H__

// Local includes:
#include "vector2.h"

// Forward declarations:
class Renderer;
class Sprite;
class InputSystem;
class ParticleEmitter;

// Class declaration:
class Cursor
{
	// Member methods:
public:
	Cursor();
	~Cursor();
	bool Initialise(Renderer& renderer);
	void Process(float deltaTime, InputSystem& inputSystem);
	void FollowMouse(InputSystem& inputSystem);
	void DebugDraw();
	void Draw(Renderer& renderer);
	Vector2& Position();

	float GetRadius();
protected:
private:
	Cursor(const Cursor& cursor);
	Cursor& operator=(const Cursor& ball);
	// Member data:
public:
protected:
	ParticleEmitter* m_pParticleEmitter;

	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_boundaryLow;
	Vector2 m_boundaryHigh;
	Sprite* m_pSprite;

	Vector2 m_xboxLeftStick;
	Vector2 m_xboxRightStick;
	int m_deadZoneX;
	int m_deadZoneY;
	float m_movementSpeed;
private:
};
#endif // __CURSOR_H__