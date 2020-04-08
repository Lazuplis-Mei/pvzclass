#include "MouseType.h"

const char* MouseType::ToString(MouseType mouset)
{
	switch (mouset)
	{
	case MouseType::None:
		return "MouseTypeNone";
	case MouseType::Card:
		return "Card";
	case MouseType::Shovel:
		return "Shovel";
	case MouseType::Crosshair:
		return "Crosshair";
	case MouseType::Watering:
		return "Watering";
	case MouseType::GoldenWatering:
		return "GoldenWatering";
	case MouseType::Fertilizer:
		return "Fertilizer";
	case MouseType::BugSpray:
		return "BugSpray";
	case MouseType::Phonograph:
		return "Phonograph";
	case MouseType::Chocolate:
		return "Chocolate";
	case MouseType::GardeningGlove:
		return "GardeningGlove";
	case MouseType::Sell:
		return "Sell";
	case MouseType::WheelBarrow:
		return "WheelBarrow";
	case MouseType::TreeFood:
		return "TreeFood";
	default:
		return "InValid_Value_Of_MouseType";
	}
}
