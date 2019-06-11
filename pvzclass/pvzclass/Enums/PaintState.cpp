#include "PaintState.h"

const char* PaintState::ToString(PaintState paints)
{
	switch (paints)
	{
	case PaintState::Normal:
		return "Normal";
	case PaintState::LightGary:
		return "LightGary";
	case PaintState::Gary:
		return "Gary";
	case PaintState::Cover:
		return "Cover";
	default:
		return "InValid_Value_Of_PaintState";
	}
}
