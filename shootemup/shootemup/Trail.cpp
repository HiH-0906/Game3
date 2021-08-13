#include <DxLib.h>
#include "Trail.h"
#include "HomingShot.h"

namespace
{
	constexpr int TrailMax = 20;
}

Trail::Trail(HomingShot& owner):
	owner_(owner)
{
	handle_ = 0;
}

void Trail::Update()
{
	history_.push_front(owner_.pos);
	if (history_.size() > TrailMax)
	{
		history_.pop_back();
	}
}

void Trail::Reset()
{
	history_.clear();
}

void Trail::SetHandle(int handle)
{
	handle_ = handle;
}

