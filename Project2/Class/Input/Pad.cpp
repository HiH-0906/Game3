#include <DxLib.h>
#include "Pad.h"

Pad::Pad()
{
	Init();
}

void Pad::Update(void)
{
	auto state = GetJoypadInputState(DX_INPUT_PAD1);
	for (auto id : INPUT_ID())
	{
		trgData_[id][static_cast<unsigned int>(TRG::OLD)] = trgData_[id][static_cast<unsigned int>(TRG::NOW)];
		trgData_[id][static_cast<unsigned int>(TRG::NOW)] = (state & config_[id]);
	}
}

bool Pad::Init(void)
{
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.8);

	config_.try_emplace(INPUT_ID::LEFT, PAD_INPUT_LEFT);
	config_.try_emplace(INPUT_ID::RIGHT, PAD_INPUT_RIGHT);
	config_.try_emplace(INPUT_ID::UP, PAD_INPUT_UP);
	config_.try_emplace(INPUT_ID::DOWN, PAD_INPUT_DOWN);
	config_.try_emplace(INPUT_ID::BTN_1, PAD_INPUT_1);
	config_.try_emplace(INPUT_ID::BTN_2, PAD_INPUT_2);
	config_.try_emplace(INPUT_ID::BTN_3, PAD_INPUT_3);

	for (auto id : INPUT_ID())
	{
		trgData_.try_emplace(id, TrgBool{ false,false });
	}

	return true;
}

const InputType Pad::GetInputType(void)
{
	return InputType::PAD;
}


