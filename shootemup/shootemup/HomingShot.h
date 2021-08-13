#pragma once
#include "Trail.h"


struct Bullet
{
	bool isActive;
	Position2f pos;
	Vector2f vel;
	bool islaser;
};

struct HomingShot:public Bullet
{
	HomingShot();
	virtual void Update(const Position2f& enePos);
	Trail trail_;
};