#include "events.h"
#include "Enums.h"
#include <vector>
#include <set>
#include <iostream>
typedef PVZ::Plant Plant;


std::vector<SPT<Plant>> EventHandler::GetAllPlants()
{
	std::vector<SPT<Plant>> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadMemory<byte>(PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xAC) + 0x141 + 0x14C * i))
			rt.push_back(MKS<Plant>(i));
	return rt;
}

std::map<int, int> PlantLastHealth;
std::map<int, bool> PlantIsDead;
std::map<int, std::pair<int, int>> PlantLastPosition;
std::map<int, std::pair<int, int>> PlantLastRowAndColumn;
std::map<int, PlantState::PlantState> PlantLastStates;

void EventHandler::UpdatePlants()
{
	if (!Address)
	{
		if(PlantList.size())
			PlantList.clear();
		if (PlantIsDead.size())
			PlantIsDead.clear();
		if (PlantLastPosition.size())
			PlantLastPosition.clear();
		if (PlantLastRowAndColumn.size())
			PlantLastRowAndColumn.clear();
		return;
	}
	// all plants list.
	std::vector<SPT<Plant>> plants = GetAllPlants();
	// The time complication is O(n^2).
	int list_num = PlantList.size();
	int plants_num = plants.size();
	for (int i = 0; i < plants_num; i++) {
		Plant* plant = plants[i].get();
		if (PlantLastHealth[plant->Index] > plant->Hp) {
			std::vector<SPT<Zombie>>zombies = GetAllZombies();
			for (int j = 0; j < zombies.size(); j++) {
				if (abs(zombies[j]->X - plant->X) <= 100) {
					InvokeEvent(new EventPlantDamage(plant, zombies[j].get()), true);
				}
			}
		}
		PlantLastHealth[plant->Index] = plant->Hp;
		PlantLastPosition[plant->Index] = std::make_pair(plant->X, plant->Y);
		PlantLastRowAndColumn[plant->Index] = std::make_pair(plant->Row, plant->Column);
		if (plant->Type == PlantType::PotatoMine && plant->State == PlantState::POTATO_SPROUT_OUT
			&& PlantLastStates[plant->Index] != PlantState::POTATO_SPROUT_OUT) {
			InvokeEvent(new EventPlantPotatoMineSproutOuted(plant), true);
		}
		if (plant->Type == PlantType::Scaredyshroon && plant->State == PlantState::SCAREDYSHROOM_SCARED
			&& PlantLastStates[plant->Index] != PlantState::SCAREDYSHROOM_SCARED) {
			InvokeEvent(new EventPlantScaredyShroonScared(plant), true);
		}
		PlantLastStates[plant->Index] = plant->State;
	}

	std::set<std::pair<int, int>> pardon;

	for (int i = 0, j = 0; i < plants_num ; i++)
	{
		Plant* plant = plants[i].get();
		for (; j < list_num; j++)
			if (PlantList[j]->BaseAddress >= plant->BaseAddress)
				break;
		if (j == list_num || PlantList[j]->BaseAddress != plant->BaseAddress)
		{
			//that means didn't found current plant in last. fire event PlantPlantEvent
			if (plant->Type >= PlantType::GatlingPea && plant->Type <= PlantType::CobCannon)
			{
				pardon.insert(std::make_pair(plant->Row, plant->Column));
				if (plant->Type == PlantType::CobCannon)
				{
					pardon.insert(std::make_pair(plant->Row, plant->Column + 1));
				}
				InvokeEvent(new EventPlantUpgrade(plant), true);
			}
			else
				InvokeEvent(new EventPlantPlant(plant), true);
			PlantIsDead[plant->Index] = false;
		}
	}

	int allPlantNum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < allPlantNum; i++) {
		Plant* plant = new Plant(i);
		if (! PlantIsDead[i] && plant->NotExist) {
			InvokeEvent(new EventPlantDead(plant, PlantLastPosition[plant->Index], PlantLastRowAndColumn[plant->Index]), true);

			PlantIsDead[i] = true;
		}
		delete(plant);
	}

	for (int i = 0, j = 0; i < list_num; i++)
	{
		Plant* plant = PlantList[i].get();
		bool ok = 1;
		for (; j < plants_num; j++)
			if (plants[j]->BaseAddress >= plant->BaseAddress)
				break;
		if (j == plants_num || plants[j]->BaseAddress != plant->BaseAddress)
		{
			//that means didn't found last plant in current. fire event PlantRemoveEvent
			if (! pardon.count(std::make_pair(plant->Row, plant->Column)))
			{
				InvokeEvent(new EventPlantRemove(plant),true);
			}
		}
	}
	pardon.clear();
	PlantList.clear();
	PlantList = plants;
}