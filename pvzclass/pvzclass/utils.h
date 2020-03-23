#pragma once
#include "PVZ.h"

namespace Utils
{
	typedef PVZ::Memory Memory;
	int read(int address)
	{
		return Memory::ReadMemory<int>(address);
	}
	void write(int address, int value)
	{
		Memory::WriteMemory(address,value);
	}
	int getPlantCost(PlantType::PlantType type)
	{
		int address = 0x69F2C0 + 0x24 * type;
		return read(address);
	}
	void setPlantCost(PlantType::PlantType type, int cost)
	{
		int address = 0x69F2C0 + 0x24 * type;
		write(address, cost);
	}
	int getPlantCooldown(PlantType::PlantType type)
	{
		int address = 0x69F2C4 + 0x24 * type;
		return read(address);
	}
	void setPlantCooldown(PlantType::PlantType type, int cooldown)
	{
		int address = 0x69F2C4 + 0x24 * type;
		write(address, cooldown);
	}
	int getPlantSpeed(PlantType::PlantType type)
	{
		int address = 0x69F2CC + 0x24 * type;
		return read(address);
	}
	void setPlantSpeed(PlantType::PlantType type, int speed)
	{
		int address = 0x69F2CC + 0x24 * type;
		write(address, speed);
	}
}