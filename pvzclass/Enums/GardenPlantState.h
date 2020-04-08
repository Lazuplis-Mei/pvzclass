#pragma once
namespace GardenPlantState
{

	enum GardenPlantState
	{
		None,
		Small,
		Medium,
		Big,
	};

	extern const char* ToString(GardenPlantState sgardenplant);

}