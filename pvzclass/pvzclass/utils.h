#pragma once
#include "Enums/PlantType.h"
#include "PVZ.h"

namespace Utils
{
	typedef PVZ::Memory Memory;
	int Read(int address)
	{
		return Memory::ReadMemory<int>(address);
	}
	void Write(int address, int value)
	{
		Memory::WriteMemory(address,value);
	}
	int GetPlantCost(PlantType::PlantType type)
	{
		int address = 0x69F2C0 + 0x24 * type;
		return Read(address);
	}
	void SetPlantCost(PlantType::PlantType type, int cost)
	{
		int address = 0x69F2C0 + 0x24 * type;
		Write(address, cost);
	}
	int GetPlantCooldown(PlantType::PlantType type)
	{
		int address = 0x69F2C4 + 0x24 * type;
		return Read(address);
	}
	void SetPlantCooldown(PlantType::PlantType type, int cooldown)
	{
		int address = 0x69F2C4 + 0x24 * type;
		Write(address, cooldown);
	}
	int GetPlantSpeed(PlantType::PlantType type)
	{
		int address = 0x69F2CC + 0x24 * type;
		return Read(address);
	}
	void SetPlantSpeed(PlantType::PlantType type, int speed)
	{
		int address = 0x69F2CC + 0x24 * type;
		Write(address, speed);
	}
	void SetSunValue(int sun)
	{
		Write(0x4309F0, sun);
	}
}