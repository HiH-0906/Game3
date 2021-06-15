#pragma once
#include <array>
#include <map>
#include "INPUT_ID.h"

enum class TRG
{
	NOW,
	OLD,
	MAX
};

enum class InputType
{
	KEYBOARD,
	PAD,
};

using TrgBool = std::array<bool, static_cast<unsigned int>(TRG::MAX)>;
using TrgData = std::map<INPUT_ID, TrgBool>;
using KeyConfig = std::map<INPUT_ID, unsigned int>;

class Controller
{
public:
	Controller();
	virtual ~Controller() = default;

	
	virtual bool Init(void) = 0;

	virtual void Update(void) = 0;

	virtual const InputType GetInputType(void) = 0;
	const TrgData& GetCntData(void);
	const bool GetTrg(INPUT_ID id);
	const bool GetNow(INPUT_ID id);

private:

protected:
	TrgData trgData_;
	KeyConfig config_;
};

