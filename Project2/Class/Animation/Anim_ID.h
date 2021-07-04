#pragma once

enum class Char_Anim_ID
{
	IDLE,
	RUN,
	CHARGE,
	CHARGE_MAX,
	MAX,
};

Char_Anim_ID begin(Char_Anim_ID);
Char_Anim_ID end(Char_Anim_ID);
Char_Anim_ID operator*(Char_Anim_ID id);
Char_Anim_ID operator++(Char_Anim_ID& key);
