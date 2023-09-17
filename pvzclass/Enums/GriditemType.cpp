#include "GriditemType.h"

const char* GriditemType::ToString(GriditemType griditemt)
{
	switch (griditemt)
	{
	case GriditemType::Grave:
		return "Grave";
	case GriditemType::Crater:
		return "Crater";
	case GriditemType::GriditemLadder:
		return "GriditemLadder";
	case GriditemType::PortalBlue:
		return "PortalBlue";
	case GriditemType::PortalYellow:
		return "PortalYellow";
	case GriditemType::AquariumBrain:
		return "Brain_In_Aquarium";
	case GriditemType::Vase:
		return "Vase";
	case GriditemType::Squirrel:
		return "Squirrel";
	case GriditemType::ZenTool:
		return "ZenTool";
	case GriditemType::Snail:
		return "Snail";
	case GriditemType::Rake:
		return "Rake";
	case GriditemType::IZBrain:
		return "Brain_In_IZ";
	default:
		return "InValid_Value_Of_GriditemType";
	}
}
