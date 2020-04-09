#pragma once
namespace MouseType
{

	enum MouseType
	{
		None,
		Card,
		Shovel = 6,
		Crosshair = 8,
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