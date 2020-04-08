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
	default:
		return "InValid_Value_Of_DamageType";
	}
}
