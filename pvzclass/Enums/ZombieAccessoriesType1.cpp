#include "ZombieAccessoriesType1.h"

const char* ZombieAccessoriesType1::ToString(ZombieAccessoriesType1 zombieat1)
{
	switch (zombieat1)
	{
	case ZombieAccessoriesType1::None:
		return "ZombieAccessoriesType1None";
	case ZombieAccessoriesType1::RoadCone:
		return "RoadCone";
	case ZombieAccessoriesType1::Bucket:
		return "Bucket";
	case ZombieAccessoriesType1::FootballCap:
		return "FootballCap";
	case ZombieAccessoriesType1::MinerHat:
		return "MinerHat";
	case ZombieAccessoriesType1::Sled:
		return "Sled";
	case ZombieAccessoriesType1::Wallnut:
		return "Wallnut";
	case ZombieAccessoriesType1::Tallnut:
		return "Tallnut";
	default:
		return "InValid_Value_Of_ZombieAccessoriesType1None";
	}
}
