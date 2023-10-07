#include "../PVZ.h"
#include "../Const.h"

int PVZ::Board::GetGridFog(int row, int column)
{
	if (row < 0 || row > 6 || column < 0 || column > 8)
		return(0);
	return(Memory::ReadMemory<int>(BaseAddress + 4 * row + 0x1C * column));
}

void PVZ::Board::GetZombieAllowed(ZombieType::ZombieType* ztypes)
{
	int p = 0;
	for (int i = 0; i < 33; i++)
	{
		if (Memory::ReadMemory<byte>(BaseAddress + 0x54D4 + i))
		{
			ztypes[p] = ZombieType::ZombieType(i);
			p++;
		}
	}
}

int PVZ::Board::GridToXPixel(int row, int column)
{
	PVZLevel::PVZLevel mode = Memory::ReadMemory<PVZLevel::PVZLevel>(Memory::ReadMemory<int>(this->BaseAddress + 0x8C) + 0x7F8);
	if (mode == PVZLevel::Zen_Garden)
	{
		SceneType::SceneType scene = this->LevelScene;
		if (scene == SceneType::Aquarium || scene == SceneType::MushroomGarden || scene == SceneType::ZenGarden)
			return(Const::GetZenGardenXPixel(row, column, scene));
	}
	return(80 * column + 40);
}

int PVZ::Board::GridToYPixel(int row, int column)
{
	PVZLevel::PVZLevel mode = Memory::ReadMemory<PVZLevel::PVZLevel>(Memory::ReadMemory<int>(this->BaseAddress + 0x8C) + 0x7F8);
	SceneType::SceneType scene = this->LevelScene;
	if (mode == PVZLevel::Zen_Garden)
	{
		if (scene == SceneType::Aquarium || scene == SceneType::MushroomGarden || scene == SceneType::ZenGarden)
			return(Const::GetZenGardenYPixel(row, column, scene));
	}
	if(scene == SceneType::Roof || scene == SceneType::MoonNight)
	{
		int offset = 0;
		if (column < 5)
			offset = 20 * (5 - column);
		return(85 * row + offset + 70);
	}
	if (scene == SceneType::Pool || scene == SceneType::Fog)
		return(85 * row + 80);
	return(100 * row + 80);
}