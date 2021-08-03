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

void Trail::Draw()
{
	auto oldPos = owner_.pos;
	auto tickness = 10.0f;
	float div = 1.0f / static_cast<float>(history_.size());
	float u = 0.0f;

	for (const auto& pos : history_)
	{
		auto v = pos - oldPos;
		v.Normalize();
		v = Vector2f(-v.y, v.x);
		auto p1 = oldPos + v * 16.0f;
		auto p2 = pos + v * 16.0f;
		auto p3 = pos - v * 16.0f;
		auto p4 = oldPos - v * 16.0f;;
		DrawRectModiGraph(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, p4.x, p4.y, u * 256, 0, div * 256, 64, handle_, true);
		u += div;
		tickness *= 0.8f;
		oldPos = pos;
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
