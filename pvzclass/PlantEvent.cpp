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

void EventHandler::InvokePlantPlantEvent(Plant* plant)
{
	int lim = FunctionPlantPlantEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantPlantEventHigh[i](plant))
			return;
	lim = FunctionPlantPlantEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantPlantEventMid[i](plant))
			return;
	lim = FunctionPlantPlantEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantPlantEventLow[i](plant))
			return;
}

void EventHandler::InvokePlantRemoveEvent(Plant* plant)
{
	int lim = FunctionPlantRemoveEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantRemoveEventHigh[i](plant))
			return;
	lim = FunctionPlantRemoveEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantRemoveEventMid[i](plant))
			return;
	lim = FunctionPlantRemoveEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantRemoveEventLow[i](plant))
			return;
}
void EventHandler::InvokePlantUpgradeEvent(Plant* plant)
{
	int lim = FunctionPlantUpgradeEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantUpgradeEventHigh[i](plant))
			return;
	lim = FunctionPlantUpgradeEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantUpgradeEventMid[i](plant))
			return;
	lim = FunctionPlantUpgradeEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionPlantUpgradeEventLow[i](plant))
			return;
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
			if (x->Type >= PlantType::GatlingPea && x->Type < PlantType::CobCannon)
			{
				//DO NOT PLANT TOO MANY PLANTS IN ONE PLACE
				std::cerr << x->Row << " " << x->Column << std::endl;
				pardon.insert(pair(x->Row, x->Column));
				InvokePlantUpgradeEvent(x);
			}
			else if (x->Type == PlantType::CobCannon)
			{
				pardon.insert(pair(x->Row, x->Column));
				pardon.insert(pair(x->Row, x->Column + 1));
				InvokePlantUpgradeEvent(x);
			}
			else
				InvokePlantPlantEvent(x);
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
				InvokePlantRemoveEvent(x);
			}
		}
	}
	pardon.clear();
	PlantList.clear();
	PlantList = plant;
}



void EventHandler::RegisterPlantPlantEvent(bool function(Plant*), int level)
{
	if(level==Event_Low)
		FunctionPlantPlantEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionPlantPlantEventMid.push_back(function);
	else if (level == Event_High)
		FunctionPlantPlantEventHigh.push_back(function);
}

void EventHandler::RegisterPlantRemoveEvent(bool function(Plant*), int level)
{
	if (level == Event_Low)
		FunctionPlantRemoveEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionPlantRemoveEventMid.push_back(function);
	else if (level == Event_High)
		FunctionPlantRemoveEventHigh.push_back(function);
}	

void EventHandler::RegisterPlantUpgradeEvent(bool function(Plant*), int level)
{
	if (level == Event_Low)
		FunctionPlantUpgradeEventLow.push_back(function);
	else if(level == Event_Mid)
		FunctionPlantUpgradeEventMid.push_back(function);
	else if (level == Event_High)
		FunctionPlantUpgradeEventHigh.push_back(function);
}
