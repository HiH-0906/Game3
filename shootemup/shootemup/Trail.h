#pragma once
#include <list>
#include "Geometry.h"

struct HomingShot;
struct HomingLaser;
class HomingShotMng;

struct Trail
{
	friend HomingShotMng;
	friend HomingLaser;
	Trail(HomingShot& owner);
	void Update();
	void Reset();
	void SetHandle(int handle);
private:
	HomingShot& owner_;
	std::list<Position2f> history_;
	int handle_;
};