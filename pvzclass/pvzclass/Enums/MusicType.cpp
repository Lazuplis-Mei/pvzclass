#include "MusicType.h"

const char* MusicType::ToString(MusicType tmusic)
{
	switch (tmusic)
	{
	case MusicType::Grasswalk:
		return "Grasswalk";
	case MusicType::Moongrains:
		return "Moongrains";
	case MusicType::WaterGraves:
		return "WaterGraves";
	case MusicType::RigorMormist:
		return "RigorMormist";
	case MusicType::CrazytheRoof:
		return "CrazytheRoof";
	case MusicType::ChooseYourSeeds:
		return "ChooseYourSeeds";
	case MusicType::CrazyDave:
		return "CrazyDave";
	case MusicType::ZenGarden:
		return "ZenGarden";
	case MusicType::Cerebrawl:
		return "Cerebrawl";
	case MusicType::Loonboon:
		return "Loonboon";
	case MusicType::UltimateBattle:
		return "UltimateBattle";
	case MusicType::BrainiacManiac:
		return "BrainiacManiac";
	default:
		return "InValid_Value_Of_MusicType";
	}
}
