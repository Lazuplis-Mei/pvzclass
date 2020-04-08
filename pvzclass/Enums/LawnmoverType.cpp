#include "LawnmoverType.h"

const char* LawnmoverType::ToString(LawnmoverType lawnmovert)
{
	switch (lawnmovert)
	{
	case LawnmoverType::LawnCleaner:
		return "LawnCleaner";
	case LawnmoverType::PoolCleaner:
		return "PoolCleaner";
	case LawnmoverType::RoofCleaner:
		return "RoofCleaner";
	case LawnmoverType::Trickedout:
		return "Trickedout";
	default:
		return "InValid_Value_Of_LawnmoverType";
	}
}
