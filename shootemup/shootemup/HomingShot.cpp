#include "HomingShot.h"


HomingShot::HomingShot():
	trail_(*this)
{
	isActive = false;
	pos = {};
	vel = {};
}
