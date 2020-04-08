#pragma once
#include "LawnTypeEnum.h"

const char* LawnType::ToString(LawnType lawnt)
{
	switch (lawnt)
	{
	case LawnType::None:
		return "LawnTypeNone";
	case LawnType::Grass:
		return "Grass";
	case LawnType::Unsodded:
		return "Unsodded";
	case LawnType::Water:
		return "Water";
	default:
		return "InValid_Value_Of_LawnType";
	}
}