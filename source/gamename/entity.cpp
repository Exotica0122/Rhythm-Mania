// COMP710 GP Framework 

// This include:  
#include "entity.h"

// Local includes: 
#include "sprite.h"
#include "vector2.h"
#include "renderer.h"

// Library includes:
#include <cmath>
#include "box2d.h"

Entity::Entity()
	: m_pSprite(0)
{

}

Entity::~Entity()
{
	delete m_pSprite;
	m_pSprite = 0;
}

void 
Entity::Rotate(float direction)
{
	float sin = sinf(direction);
	float cos = cosf(direction);

	float tx = m_velocity.x;
	float ty = m_velocity.y;
	m_velocity.x = (cos * tx) - (sin * ty);
	m_velocity.y = (sin * tx) + (cos * ty);
}

bool 
Entity::IsAlive() const
{
	return m_bAlive;
}

void 
Entity::SetDead()
{
	m_bAlive = false;
}

float 
Entity::GetRadius()
{
	float radius = m_pSprite->GetWidth() / 2;
	return radius;
}

Vector2 
Entity::GetFacingDirection()
{
	// Plz check this back
	float normalised = sqrt(pow(m_velocity.x, 2) + pow(m_velocity.y, 2));
	Vector2 unitVector = { m_velocity.x / normalised, m_velocity.y / normalised };
	return unitVector;
}

Vector2& 
Entity::GetPosition()
{
	return m_position;
}

Vector2& 
Entity::GetVelocity()
{
	return m_velocity;
}

bool 
Entity::IsCollidingWith(Entity& toCheck)
{
	float x1 = GetPosition().x;
	float y1 = GetPosition().y;

	float x2 = toCheck.GetPosition().x;
	float y2 = toCheck.GetPosition().y;

	float r1 = GetRadius();
	float r2 = toCheck.GetRadius();

	float distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) - r1 - r2;

	return (distance <= 0);
}