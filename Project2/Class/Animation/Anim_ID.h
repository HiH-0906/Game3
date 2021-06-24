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
Anim_ID operator++(Anim_ID& key);
