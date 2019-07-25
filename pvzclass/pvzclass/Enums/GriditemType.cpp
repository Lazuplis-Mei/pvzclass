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
	case GriditemType::Brain:
		return "Brain";
	case GriditemType::Vase:
		return "Vase";
	case GriditemType::Snail:
		return "Snail";
	case GriditemType::Rake:
		return "Rake";
	default:
		return "InValid_Value_Of_GriditemType";
	}
}
