#pragma once
#include <list>
#include "Geometry.h"

struct HomingShot;

struct Trail
{
	Trail(HomingShot& owner);
	void Update();
	void Draw();
	void Reset();
	void SetHandle(int handle);
private:
	HomingShot& owner_;
	std::list<Position2f> history_;
	int handle_;
};