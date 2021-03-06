#include <DxLib.h>
#include "Controller.h"
#include "../../_debug/_DebugDispOut.h"

Controller::Controller()
{
	// RingBufの作成 @@ここ以外で呼び出すことがあるなら個別関数化
	auto CreatRingBuf = [&](unsigned int num)
	{
		RingBuf* ringBuf= new RingBuf();
		RingBuf* firstRingBuf = ringBuf;
		for (unsigned int i = 1; i < num; i++)
		{
			ringBuf->next_ = new RingBuf();
			ringBuf->next_->befor_ = ringBuf;
			ringBuf = ringBuf->next_;
		}
		firstRingBuf->befor_ = ringBuf;
		ringBuf->next_ = firstRingBuf;
		return firstRingBuf;
	};

	ringBuf_ = CreatRingBuf(30);


	chengCMDtoINPUTMap_ = {
		{CMD_ID::NEUTRAL,5},
		{CMD_ID::LEFT_U,7},
		{CMD_ID::LEFT_D,1},
		{CMD_ID::RIGHT_U,9},
		{CMD_ID::RIGHT_D,3},
		{CMD_ID::LEFT,4},
		{CMD_ID::RIGHT,6},
		{CMD_ID::UP,8},
		{CMD_ID::DOWN,2},
		{CMD_ID::BTN_1,10},
		{CMD_ID::BTN_2,11},
		{CMD_ID::BTN_3,12},
	};
}

Controller::~Controller()
{
	auto now = ringBuf_->next_;
	ringBuf_->next_ = nullptr;

	while (now != nullptr)
	{
		auto del = now->next_;
		delete now;
		now = del;
	}
	ringBuf_ = nullptr;
}

void Controller::UpdateRingBuf(const double& delta)
{
	ringBuf_ = ringBuf_->next_;
	unsigned int check = 0;
	for (const auto& id :INPUT_ID())
	{
		if (GetNow(id))
		{
			check |= static_cast<unsigned int>(id);
		}
	}
	ringBuf_->id_ = check;
	ringBuf_->num = chengCMDtoINPUTMap_[static_cast<CMD_ID>(check)];
	ringBuf_->time_ = delta;
	return;
}

void Controller::DebugRingBuf(void)
{
#ifdef _DEBUG
	_dbgDrawBox(0, 580, 1024, 620,0x000000,true);
	int cnt = 0;
	for (auto buf = ringBuf_->befor_; buf != ringBuf_; buf = buf->befor_)
	{
		_dbgDrawFormatString(16 + cnt * 24, 580, 0xffffff, "%d", cnt);
		_dbgDrawFormatString(16 + cnt++ * 24, 600, 0xffffff, "%d", buf->num);
	}
	_dbgDrawFormatString(16 + cnt * 24, 580, 0xffffff, "%d", cnt);
	_dbgDrawFormatString(16 + cnt++ * 24, 600, 0xffffff, "%d", ringBuf_->num);
#endif // DEBUG
	
}

const TrgData& Controller::GetCntData(void)
{
	return trgData_;
}

const bool Controller::GetTrg(INPUT_ID id)
{
	return trgData_[id][static_cast<unsigned int>(TRG::NOW)]&& !trgData_[id][static_cast<unsigned int>(TRG::OLD)];
}

const bool Controller::GetNow(INPUT_ID id)
{
	return trgData_[id][static_cast<unsigned int>(TRG::NOW)];
}

const Controller::RingBuf* Controller::GetRingBuf(void)
{
	return ringBuf_;
}
