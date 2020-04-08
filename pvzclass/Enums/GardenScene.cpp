#include "GardenScene.h"

const char* GardenScene::ToString(GardenScene gardens)
{
	switch (gardens)
	{
	case GardenScene::ZenGarden:
		return "ZenGarden";
	case GardenScene::MushroomGarden:
		return "MushroomGarden";
	case GardenScene::WheelBarrow:
		return "WheelBarrow";
	case GardenScene::Aquarium:
		return "Aquarium";
	default:
		return "InValid_Value_Of_GardenScene";
	}
}
