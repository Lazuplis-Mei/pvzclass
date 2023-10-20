#include "../PVZ.h"

PVZ::PlantDefinition::PlantDefinition(PlantType::PlantType type)
{
	BaseAddress = 0x69F2B0 + 0x24 * type;
}

PVZ::ZombieDefinition::ZombieDefinition(ZombieType::ZombieType type)
{
	BaseAddress = 0x69DA80 + 0x1C * type;
}

PVZ::ProjectileDefinition::ProjectileDefinition(ProjectileType::ProjectileType type)
{
	BaseAddress = 0x69F1C0 + 0xC * type;
}

PVZ::ChallengeDefinition::ChallengeDefinition(PVZLevel::PVZLevel mode)
{
	BaseAddress = 0x6A2B88 + 0x18 * mode;
}