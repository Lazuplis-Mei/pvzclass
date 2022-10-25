#pragma once
namespace PlantEffectType
{

	enum PlantEffectType
	{
		CherryBombEffect = 2,
		PotatoMineEffect = 4,
		IceshroomEffect = 14,
		DoomshroomEffect = 15,
		JalapenoEffect = 20,
		BloverEffect = 27,
	};

	extern const char* ToString(PlantEffectType plantef);

}