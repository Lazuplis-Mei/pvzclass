#include "PlantEffectType.h"

const char* PlantEffectType::ToString(PlantEffectType plantef)
{
	switch (plantef)
	{
	case PlantEffectType::CherryBombEffect:
		return "CherryBombEffect";
	case PlantEffectType::PotatoMineEffect:
		return "PotatoMineEffect";
	case PlantEffectType::IceshroonEffect:
		return "IceshroonEffect";
	case PlantEffectType::DoomshroonEffect:
		return "DoomshroonEffect";
	case PlantEffectType::JalapenoEffect:
		return "JalapenoEffect";
	case PlantEffectType::BloverEffect:
		return "BloverEffect";
	default:
		return "InValid_Value_Of_PlantEffectType";
	}
}
