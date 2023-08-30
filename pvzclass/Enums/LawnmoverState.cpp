#include "LawnmoverState.h"

const char* LawnmoverState::ToString(LawnmoverState lawnmovert)
{
	switch (lawnmovert)
	{
	case LawnmoverState::RollingIn:
		return "RollingIn";
	case LawnmoverState::Ready:
		return "Ready";
	case LawnmoverState::Triggered:
		return "Triggered";
	case LawnmoverState::Squished:
		return "Squished";
	default:
		return "InValid_Value_Of_LawnmoverState";
	}
}
