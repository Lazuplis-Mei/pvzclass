#include "SceneType.h"

const char* SceneType::ToString(SceneType scenet)
{
	switch (scenet)
	{
	case SceneType::Day:
		return "Day";
	case SceneType::Night:
		return "Night";
	case SceneType::Pool:
		return "Pool";
	case SceneType::Fog:
		return "Fog";
	case SceneType::Roof:
		return "Roof";
	case SceneType::MoonNight:
		return "MoonNight";
	case SceneType::MushroomGarden:
		return "MushroomGarden";
	case SceneType::ZenGarden:
		return "ZenGarden";
	case SceneType::Aquarium:
		return "Aquarium";
	case SceneType::TreeofWisdom:
		return "TreeofWisdom";
	default:
		return "InValid_Value_Of_SceneType";
	}
}
