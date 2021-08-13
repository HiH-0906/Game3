#include "HomingShot.h"

namespace
{
	constexpr float homing_Shot_Speed = 10.0f;
}

HomingShot::HomingShot():
	trail_(*this)
{
	isActive = false;
	pos = {};
	vel = {};
}

void HomingShot::Update(const Position2f& enePos)
{
	trail_.Update();
	pos += vel;
	// 思ったより出来が良かった版sin,cos版と遜色ないならこっちでいい疑惑
	vel = (vel + (enePos - pos).Normalized()).Normalized() * homing_Shot_Speed;

	// 敵との当たり判定
	if ((enePos - pos).SQMagnitude() < 900.0f)
	{
		isActive = false;
	}
	// 画面外判定
	if (pos.x + 16 < 0 || pos.x - 16 > 640 ||
		pos.y + 24 < 0 || pos.y - 24 > 480)
	{
		isActive = false;
	}
}
