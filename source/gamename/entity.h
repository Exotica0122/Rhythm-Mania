// COMP710 GP Framework 2022
#ifndef __ENTITY_H__
#define __ENTITY_H__

// Local includes:
#include "vector2.h"

// Forward declarations: 
class Renderer;
class Sprite;

// Class declaration: 
class Entity
{
	// Member methods: 
public:
	Entity();
	virtual ~Entity();
	virtual bool Initialise(Renderer& renderer) = 0;
	virtual void Process(float deltaTime) = 0;
	virtual void Draw(Renderer& renderer) = 0;
	void Rotate(float direction);
	bool IsAlive() const;
	void SetDead();
	float GetRadius();
	Vector2 GetFacingDirection();
	Vector2& GetPosition();
	Vector2& GetVelocity();
	bool IsCollidingWith(Entity& toCheck);
protected:
private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);
	// Member data: 
public:
protected:
	Sprite* m_pSprite;
	Vector2 m_position;
	Vector2 m_velocity;
	bool m_bAlive;
private:
};
#endif // __ENTITY_H__