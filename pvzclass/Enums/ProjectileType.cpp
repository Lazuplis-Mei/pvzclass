#include "ProjectileType.h"

const char* ProjectileType::ToString(ProjectileType projectilet)
{
	switch (projectilet)
	{
	case ProjectileType::Pea:
		return "Pea";
	case ProjectileType::SnowPea:
		return "SnowPea";
	case ProjectileType::Cabbage:
		return "Cabbage";
	case ProjectileType::Melon:
		return "Melon";
	case ProjectileType::Puff:
		return "Puff";
	case ProjectileType::WinterMelon:
		return "WinterMelon";
	case ProjectileType::FirePea:
		return "FirePea";
	case ProjectileType::Star:
		return "Star";
	case ProjectileType::Cactus:
		return "Cactus";
	case ProjectileType::Basketball:
		return "Basketball";
	case ProjectileType::Kernel:
		return "Kernel";
	case ProjectileType::CobCannon:
		return "CobCannon";
	case ProjectileType::Butter:
		return "Butter";
	case ProjectileType::ZombiePea:
		return "ZombiePea";
	default:
		return "InValid_Value_Of_ProjectileType";
	}
}
