#include ".\GardenPlantNeed.h"

const char* GardenPlantNeed::ToString(GardenPlantNeed gardenplant_need)
{
	switch (gardenplant_need)
	{
	case GardenPlantNeed::None:
		return "None";
	case GardenPlantNeed::Water:
		return "Water";
	case GardenPlantNeed::Fertilizer:
		return "Fertilizer";
	case GardenPlantNeed::BugSpray:
		return "BugSpray";
	case GardenPlantNeed::Phonograph:
		return "Phonograph";
	default:
		return "InValid_Value_Of_GardenPlantNeed";
	}
}
