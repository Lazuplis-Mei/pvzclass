#include "DamageType.h"

const char* DamageType::ToString(DamageType damaget)
{
	switch (damaget)
	{
	case DamageType::Direct:
		return "Direct";
	case DamageType::Side:
		return "Side";
	case DamageType::Sputter:
		return "Sputter";
	case DamageType::Direct_Ice:
		return "Direct_Ice";
	case DamageType::Side_Ice:
		return "Side_Ice";
	case DamageType::Sputter_Ice:
		return "Sputter_Ice";
	case DamageType::Direct_AntiVehicle:
		return "Direct_AntiVehicle";
	case DamageType::Side_AntiVehicle:
		return "Side_AntiVehicle";
	case DamageType::Sputter_AntiVehicle:
		return "Sputter_AntiVehicle";
	case DamageType::Direct_Ice_AntiVehicle:
		return "Direct_Ice_AntiVehicle";
	case DamageType::Side_Ice_AntiVehicle:
		return "Side_Ice_AntiVehicle";
	case DamageType::Sputter_Ice_AntiVehicle:
		return "Sputter_Ice_AntiVehicle";
	default:
		return "InValid_Value_Of_DamageType";
	}
}
