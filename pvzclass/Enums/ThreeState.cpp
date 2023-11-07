#include "ThreeState.h"

const char* ThreeState::ToString(ThreeState state)
{
	switch (state)
	{
	case ThreeState::Disable:
		return "Disable";
	case ThreeState::None:
		return "None";
	case ThreeState::Enable:
		return "Enable";
	default:
		return "InValid_Value_Of_ThreeState";
	}
}
