#include "Controller.h"

Controller::Controller()
{
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
