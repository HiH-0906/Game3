#pragma once

enum class Anim_ID
{
	IDLE,
	RUN,
	CHARGE,
	CHARGE_MAX,
	MAX,
};

Anim_ID begin(Anim_ID);
Anim_ID end(Anim_ID);
Anim_ID operator*(Anim_ID id);
Anim_ID operator++(Anim_ID& key);
