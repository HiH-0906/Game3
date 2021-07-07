#pragma once
#include "../Object/Object.h"

struct Idel
{
	bool operator()(Object& obj)
	{
		return true;
	}
};