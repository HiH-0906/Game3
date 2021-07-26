#pragma once

enum class INPUT_ID
{
	UP = 1,
	DOWN = 2,
	LEFT = 4,
	RIGHT = 8,
	BTN_1 = 16,
	BTN_2 = 32,
	BTN_3 = 64,
	MAX = 128
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

enum class CMD_ID
{
	UP = 1,
	DOWN = 2,
	LEFT = 4,
	RIGHT = 8,
	LEFT_U = UP + LEFT,
	LEFT_D = DOWN + LEFT,
	RIGHT_U = UP + RIGHT,
	RIGHT_D = DOWN + RIGHT,
	BTN_1 = 16,
	BTN_2 = 32,
	BTN_3 = 64,
	MAX,
	NEUTRAL = 0,
};

enum class InputType
{
	KEYBOARD,
	PAD,
};
