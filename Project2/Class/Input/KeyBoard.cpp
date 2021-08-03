#include <DxLib.h>
#include "KeyBoard.h"

KeyBoard::KeyBoard()
{
	Init();
}

bool KeyBoard::Init(void)
{
	config_ = {
		{INPUT_ID::LEFT, KEY_INPUT_LEFT},
		{INPUT_ID::RIGHT, KEY_INPUT_RIGHT},
		{INPUT_ID::UP, KEY_INPUT_UP},
		{INPUT_ID::DOWN, KEY_INPUT_DOWN},
		{INPUT_ID::BTN_1, KEY_INPUT_SPACE},
		{INPUT_ID::BTN_2, KEY_INPUT_X},
		{INPUT_ID::BTN_3, KEY_INPUT_C},
	};

	for (auto id:INPUT_ID())
	{
		trgData_.try_emplace(id, TrgBool{ false,false });
	}
	return true;
}

void KeyBoard::Update(void)
{
	for (auto id : INPUT_ID())
	{
		trgData_[id][static_cast<unsigned int>(TRG::OLD)] = trgData_[id][static_cast<unsigned int>(TRG::NOW)];
		trgData_[id][static_cast<unsigned int>(TRG::NOW)] = CheckHitKey(config_[id]);
	}
}

const InputType KeyBoard::GetInputType(void)
{
	return InputType::KEYBOARD;
}
