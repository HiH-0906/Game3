#pragma once
#include "Trail.h"


struct Bullet
{
	bool isActive;
	Position2f pos;
	Vector2f vel;
};

struct HomingShot:public Bullet
{
	HomingShot();
	Trail trail_;
};