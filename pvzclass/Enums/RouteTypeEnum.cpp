#include "RouteTypeEnum.h"

const char* RouteType::ToString(RouteType routet)
{
	switch (routet)
	{
	case RouteType::None:
		return "RouteTypeNone";
	case RouteType::NoZombie:
		return "NoZombie";
	case RouteType::Land:
		return "Land";
	case RouteType::Pool:
		return "Pool";
	default:
		return "InValid_Value_Of_RouteType";
	}
}
