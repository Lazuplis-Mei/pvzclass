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

void EventHandler::UpdatePlants()
{
	if (!Address)
	{
		if(PlantList.size())
			PlantList.clear();
		return;
	}
	std::vector<Plant*> plant = GetAllPlants();
	std::set<pair> pardon;
	// another plant is list.
	// The time complication is O(n^2).
	int listn = PlantList.size();
	int plantn = plant.size();
	for (int i = 0; i < plantn; i++)
	{
		Plant* x = plant[i];
		bool ok = 1;
		for (int j = 0; j < listn; j++)
			if (x->BaseAddress == PlantList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//that means didn't found current x in last. fire event PlantPlantEvent
			if (x->Type >= PlantType::GatlingPea && x->Type <= PlantType::CobCannon)
			{
				pardon.insert(pair(x->Row, x->Column));
				if(x->Type == PlantType::CobCannon)
				{
					pardon.insert(pair(x->Row, x->Column + 1));
				}
				InvokeEvent(new EventPlantUpgrade(x),true);
			}
			else
				InvokeEvent(new EventPlantPlant(x),true);
		}
	}
	//if (pardon.size())std::cerr << "LIST:" << std::endl;
	//for (pair p : pardon)
	//	std::cerr << p.first << " " << p.second << std::endl;
	for (int i = 0; i < listn; i++)
	{
		Plant* x = PlantList[i];
		bool ok = 1;
		for (int j = 0; j < plantn; j++)
			if (x->BaseAddress == plant[j]->BaseAddress)
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
				InvokeEvent(new EventPlantRemove(x),true);
			}
		}
	}
	pardon.clear();
	PlantList.clear();
	PlantList = plant;
}