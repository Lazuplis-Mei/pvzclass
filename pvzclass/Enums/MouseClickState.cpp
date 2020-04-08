#include "MouseClickState.h"

const char* MouseClickState::ToString(MouseClickState mousecs)
{
	switch (mousecs)
	{
	case MouseClickState::None:
		return "MouseClickStateNone";
	case MouseClickState::LButton:
		return "LButton";
	case MouseClickState::RButton:
		return "RButton";
	case MouseClickState::LRButton:
		return "LRButton";
	case MouseClickState::MidButto:
		return "MidButto";
	case MouseClickState::LMidButton:
		return "LMidButton";
	case MouseClickState::RMidButton:
		return "RMidButton";
	case MouseClickState::LRMidButton:
		return "LRMidButton";
	default:
		return "InValid_Value_Of_MouseClickState";
	}
}
