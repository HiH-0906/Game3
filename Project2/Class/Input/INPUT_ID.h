#pragma once

enum class INPUT_ID
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BTN_1,
	BTN_2,
	BTN_3,
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator++(INPUT_ID& key);
INPUT_ID operator*(INPUT_ID key);


enum class TRG
{
	NOW,
	OLD,
	MAX
};
