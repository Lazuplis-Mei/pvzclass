#pragma once
namespace MouseType
{

	enum MouseType
	{
		None,
		SlotPlant,
		CoinPlant,
		GlovePlant,
		DuplicatorPlant,
		WheelBarrowPlant,
		Shovel,
		Hammer,
		Crosshair,
		Watering,
		GoldenWatering,
		Fertilizer,
		BugSpray,
		Phonograph,
		Chocolate,
		GardeningGlove,
		Sell,
		WheelBarrow,
		TreeFood,
	};

	extern const char* ToString(MouseType mouset);

}