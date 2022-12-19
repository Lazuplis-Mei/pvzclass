#pragma once
namespace GardenPlantNeed
{

	enum GardenPlantNeed
	{
		None = 0,
		Water,
		Fertilizer,
		BugSpray,
		Phonograph
	};

	extern const char* ToString(GardenPlantNeed captions);

}