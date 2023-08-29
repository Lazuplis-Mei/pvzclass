#include "../PVZ.h"

PVZ::PlantDefinition::PlantDefinition(int id)
{
	BaseAddress = 0x69F2B0 + 0x24 * id;
}

PVZ::ZombieDefinition::ZombieDefinition(int id)
{
	BaseAddress = 0x69DA80 + 0x1C * id;
}

PVZ::ProjectileDefinition::ProjectileDefinition(ProjectileType::ProjectileType id)
{
	BaseAddress = 0x69F1C0 + 0xC * id;
}