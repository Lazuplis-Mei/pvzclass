#include "GardenPlantState.h"

const char* GardenPlantState::ToString(GardenPlantState sgardenplant)
{
	switch (sgardenplant)
	{
	case GardenPlantState::None:
		return "GardenPlantStateNone";
	case GardenPlantState::Small:
		return "Small";
	case GardenPlantState::Medium:
		return "Medium";
	case GardenPlantState::Big:
		return "Big";
	default:
		return "InValid_Value_Of_GardenPlantState";
	}
}
