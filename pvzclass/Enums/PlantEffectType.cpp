#include "PlantEffectType.h"

const char* PlantEffectType::ToString(PlantEffectType plantef)
{
	switch (plantef)
	{
	case PlantEffectType::CherryBombEffect:
		return "CherryBombEffect";
	case PlantEffectType::PotatoMineEffect:
		return "PotatoMineEffect";
	case PlantEffectType::IceshroomEffect:
		return "IceshroomEffect";
	case PlantEffectType::DoomshroomEffect:
		return "DoomshroomEffect";
	case PlantEffectType::JalapenoEffect:
		return "JalapenoEffect";
	case PlantEffectType::BloverEffect:
		return "BloverEffect";
	default:
		return "InValid_Value_Of_PlantEffectType";
	}
}
