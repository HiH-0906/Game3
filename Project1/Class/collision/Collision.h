#pragma once
#include <vector>
#include <memory>
#include "../../common/Vector2.h"

enum class COLLISION_TAG
{
	Square,
	Circle,
	Triangle
};

class Shape;

class Collision
{
public:
	Collision(const Vector2Flt offset);
	virtual ~Collision();

	void SetOwner(std::shared_ptr<Shape> owner);

	virtual  COLLISION_TAG CollisionTag(void) = 0;

	virtual bool isHit(std::shared_ptr<Collision> col) = 0;

	virtual bool CheckHitWall(const Vector2& scrSize,bool& UpDown) = 0;
protected:
	std::shared_ptr<Shape> owner_;
	Vector2Flt offset_;
};

