#include "HomingLaser.h"


namespace
{
	constexpr float homing_Shot_Speed = 10.0f;
}

HomingLaser::HomingLaser(char& isButton, Position2f& pos):
	isButton_(isButton),ownerPos_(pos)
{
}

void HomingLaser::Update(const Position2f& enePos)
{
	if (!isButton_)
	{
		isActive = false;
	}
	trail_.Reset();
	auto tmpPos = ownerPos_;
	auto tmpVel = vel;
	while (!((enePos - tmpPos).SQMagnitude() < 900.0f))
	{
		trail_.history_.push_front(tmpPos);
		tmpPos += tmpVel;
		// 思ったより出来が良かった版sin,cos版と遜色ないならこっちでいい疑惑
		tmpVel = (tmpVel + (enePos - tmpPos).Normalized()).Normalized() * homing_Shot_Speed;
		if (tmpPos.y + 24 < 0 || tmpPos.y - 24 > 480)
		{
			break;
		}
	}
}
