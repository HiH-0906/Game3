#include <DxLib.h>
#include "Trail.h"
#include "HomingShot.h"

namespace
{
	constexpr int TrailMax = 10;
}

Trail::Trail(HomingShot& owner):
	owner_(owner)
{
}

void Trail::Update()
{
	history_.push_front(owner_.pos);
	if (history_.size() > TrailMax)
	{
		history_.pop_back();
	}
}

void Trail::Draw()
{
	auto oldPos = owner_.pos;
	auto tickness = 10.0f;
	float div = 1.0f / static_cast<float>(history_.size());

	for (const auto& trail : history_)
	{
		DrawLineAA(oldPos.x, oldPos.y, trail.x, trail.y, 0xffffff, tickness);
		tickness *= 0.8f;
		oldPos = trail;
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
