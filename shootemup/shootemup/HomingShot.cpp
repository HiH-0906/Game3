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
	// �v�������o�����ǂ�������sin,cos�łƑ��F�Ȃ��Ȃ炱�����ł����^�f
	vel = (vel + (enePos - pos).Normalized()).Normalized() * homing_Shot_Speed;

	// �G�Ƃ̓����蔻��
	if ((enePos - pos).SQMagnitude() < 900.0f)
	{
		isActive = false;
	}
	// ��ʊO����
	if (pos.x + 16 < 0 || pos.x - 16 > 640 ||
		pos.y + 24 < 0 || pos.y - 24 > 480)
	{
		isActive = false;
	}
}
