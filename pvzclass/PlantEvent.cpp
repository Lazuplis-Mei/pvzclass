#include "events.h"
#include "Enums.h"
#include <vector>
#include <set>
#include <iostream>
typedef PVZ::Plant Plant;


std::vector<Plant*> EventHandler::GetAllPlants()
{
	std::vector<Plant*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadMemory<byte>(PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xAC) + 0x141 + 0x14C * i))
			rt.push_back(new Plant(i));
	return rt;
}

std::map<int, int> PlantLastHealth;
std::map<int, bool> PlantIsDead;
std::map<int, std::pair<int, int>> PlantLastPosition;
std::map<int, std::pair<int, int>> PlantLastRowAndColumn;

void EventHandler::UpdatePlants()
{
	if (!Address)
	{
		if(PlantList.size())
			PlantList.clear();
		return;
	}
	// all plants list.
	std::vector<Plant*> plants = GetAllPlants();
	// The time complication is O(n^2).
	int list_num = PlantList.size();
	int plants_num = plants.size();
	for (int i = 0; i < plants_num; i++) {
		Plant* plant = plants[i];
		if (PlantLastHealth[i] > plants[i]->Hp) {
			std::vector<Zombie*>zombies = GetAllZombies();
			for (int j = 0; j < zombies.size(); j++) {
				if (abs(zombies[j]->X - plant->X) <= 100) {
					InvokeEvent(new EventPlantDamage(plant, zombies[j]), true);
				}
			}
		}
		PlantLastHealth[plant->Index] = plant->Hp;
		PlantLastPosition[plants[i]->Index] = std::make_pair(plant->X, plant->Y);
		PlantLastRowAndColumn[plants[i]->Index] = std::make_pair(plant->Row, plant->Column);
	}

	std::set<std::pair<int, int>> pardon;
	for (int i = 0; i < plants_num; i++)
	{
		Plant* plant = plants[i];
		bool ok = 1;
		for (int j = 0; j < list_num; j++)
			if (plant->BaseAddress == PlantList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//that means didn't found current plant in last. fire event PlantPlantEvent
			if (plant->Type >= PlantType::GatlingPea && plant->Type <= PlantType::CobCannon)
			{
				pardon.insert(std::make_pair(plant->Row, plant->Column));
				if(plant->Type == PlantType::CobCannon)
				{
					pardon.insert(std::make_pair(plant->Row, plant->Column + 1));
				}
				InvokeEvent(new EventPlantUpgrade(plant),true);
			}
			else
				InvokeEvent(new EventPlantPlant(plant),true);
			PlantIsDead[plant->Index] = false;
		}
	}

	int allPlantNum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < allPlantNum; i++) {
		Plant* plant = new Plant(i);
		if (! PlantIsDead[i] && plant->NotExist) {
			InvokeEvent(new EventPlantDead(plant, PlantLastPosition[i], PlantLastRowAndColumn[plants[i]->Index]), true);
			PlantIsDead[i] = true;
		}
	}

	for (int i = 0; i < list_num; i++)
	{
		Plant* plant = PlantList[i];
		bool ok = 1;
		for (int j = 0; j < plants_num; j++)
			if (plant->BaseAddress == plants[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//that means didn't found last plant in current. fire event PlantRemoveEvent
			if (! pardon.count(std::make_pair(plant->Row, plant->Column)))
			{
				//std::cerr << "didn't find\n";
				InvokeEvent(new EventPlantRemove(plant),true);
			}
		}
	}
	pardon.clear();
	PlantList.clear();
	PlantList = plants;
}