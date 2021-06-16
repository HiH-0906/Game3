#include "Collision.h"
#include "../Shape.h"

Collision::Collision(const Vector2Flt offset)
{
}

Collision::~Collision()
{
}

void Collision::SetOwner(std::shared_ptr<Shape> owner)
{
	owner_ = owner;
}

