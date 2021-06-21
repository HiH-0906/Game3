#pragma once

enum class Anim_ID
{
	IDLE,
	RUN,
	MAX,
};

Anim_ID begin(Anim_ID);
Anim_ID operator++(Anim_ID& key);
