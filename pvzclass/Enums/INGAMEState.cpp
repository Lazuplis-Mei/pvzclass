#include "INGAMEState.h"

const char* INGAMEState::ToString(INGAMEState ingames)
{
	switch (ingames)
	{
	case INGAMEState::None:
		return "INGAMEStateNone";
	case INGAMEState::Starting:
		return "Starting";
	case INGAMEState::Finished:
		return "Finished";
	case INGAMEState::Disappearing:
		return "Disappearing";
	default:
		return "InValid_Value_Of_INGAMEState";
	}
}
