#include "events.h"
#include "Enums.h"
#include <vector>
#include <set>
#include <iostream>
typedef PVZ::Plant Plant;


std::vector<Plant*> EventHandler::getAllPlants()
{
	std::vector<Plant*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xB0);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadMemory<byte>(PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xAC) + 0x141 + 0x14C * i))
			rt.push_back(new Plant(i));
	return rt;
}
bool EventHandler::equals(Plant* a, Plant* b)
{
	return a->BaseAddress == b->BaseAddress;
}

void EventHandler::invokePlantPlantEvent(Plant* plant)
{
	int lim = functionPlantPlantEvent.size();
	for (int i = 0; i < lim; i++)
		functionPlantPlantEvent[i](plant);
}

void EventHandler::invokePlantRemoveEvent(Plant* plant)
{
	int lim = functionPlantRemoveEvent.size();
	for (int i = 0; i < lim; i++)
		functionPlantRemoveEvent[i](plant);
}
void EventHandler::invokePlantUpgradeEvent(Plant* plant)
{
	int lim = functionPlantUpgradeEvent.size();
	for (int i = 0; i < lim; i++)
		functionPlantUpgradeEvent[i](plant);
}
struct pair
{
	int first, second;
	pair(int a, int b)
	{
		first = a;
		second = b;
	}
	bool operator == (pair b)
	{
		return first == b.first && second == b.second;
	}
};
bool operator < (pair a, pair b)
{
	return a.first == b.first ? a.second < b.second : a.first < b.first;
}
void EventHandler::updatePlants()
{
	if (!address)
	{
		if(list.size())
			list.clear();
		return;
	}
	std::vector<Plant*> plant = getAllPlants();
	std::set<pair> pardon;
	// another plant is list.
	// The time complication is O(n^2).
	int listn = list.size();
	int plantn = plant.size();
	for (int i = 0; i < plantn; i++)
	{
		Plant* x = plant[i];
		bool ok = 1;
		for (int j = 0; j < listn; j++)
			if (equals(x, list[j]))
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//that means didn't found current x in last. fire event PlantPlantEvent
			if (x->Type >= PlantType::GatlingPea && x->Type < PlantType::CobCannon)
			{
				//DO NOT PLANT TOO MANY PLANTS IN ONE PLACE
				std::cerr << x->Row << " " << x->Column << std::endl;
				pardon.insert(pair(x->Row, x->Column));
				invokePlantUpgradeEvent(x);
			}
			else if (x->Type == PlantType::CobCannon)
			{
				pardon.insert(pair(x->Row, x->Column));
				pardon.insert(pair(x->Row, x->Column + 1));
				invokePlantUpgradeEvent(x);
			}
			else
				invokePlantPlantEvent(x);
		}
	}
	//if (pardon.size())std::cerr << "LIST:" << std::endl;
	//for (pair p : pardon)
	//	std::cerr << p.first << " " << p.second << std::endl;
	for (int i = 0; i < listn; i++)
	{
		Plant* x = list[i];
		bool ok = 1;
		for (int j = 0; j < plantn; j++)
			if (equals(x, plant[j]))
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//that means didn't found last x in current. fire event PlantRemoveEvent
			if (!pardon.count(pair(x->Row, x->Column)))
			{
				//std::cerr << "didn't find\n";
				invokePlantRemoveEvent(x);
			}
		}
	}
	pardon.clear();
	list.clear();
	list = plant;
}



void EventHandler::registerPlantPlantEvent(void function(Plant*))
{
	functionPlantPlantEvent.push_back(function);
}

void EventHandler::registerPlantRemoveEvent(void function(Plant*))
{
	functionPlantRemoveEvent.push_back(function);
}

void EventHandler::registerPlantUpgradeEvent(void function(Plant*))
{
	functionPlantUpgradeEvent.push_back(function);
}
