#include "events.h"

typedef PVZ::Zombie Zombie;

std::vector<Zombie*> EventHandler::GetAllZombies()
{
	std::vector<Zombie*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt.push_back(new Zombie(i));
	return rt;
}

void EventHandler::InvokeZombieSpawnEvent(Zombie* zombie)
{
	int lim = FunctionZombieSpawnEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieSpawnEventHigh[i](zombie))
			return; 
	lim = FunctionZombieSpawnEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieSpawnEventMid[i](zombie))
			return;
	lim = FunctionZombieSpawnEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieSpawnEventLow[i](zombie))
			return;
}
void EventHandler::InvokeZombieRemoveEvent(Zombie* zombie)
{
	int lim = FunctionZombieRemoveEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieRemoveEventHigh[i](zombie))
			return; 
	lim = FunctionZombieRemoveEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieRemoveEventMid[i](zombie))
			return;
	lim = FunctionZombieRemoveEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieRemoveEventLow[i](zombie))
			return;
}
void EventHandler::InvokeZombieDeadEvent(Zombie* zombie)
{
	int lim = FunctionZombieDeadEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieDeadEventHigh[i](zombie))
			return; 
	lim = FunctionZombieDeadEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieDeadEventMid[i](zombie))
			return;
	lim = FunctionZombieDeadEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieDeadEventLow[i](zombie))
			return;
}

void EventHandler::InvokeZombieHypnotizedEvent(Zombie* zombie)
{
	int lim = FunctionZombieHypnotizedEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieHypnotizedEventHigh[i](zombie))
			return;
	lim = FunctionZombieHypnotizedEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieHypnotizedEventMid[i](zombie))
			return;
	lim = FunctionZombieHypnotizedEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionZombieHypnotizedEventLow[i](zombie))
			return;
}

bool isPostedZombieDead[10000] = {};
bool isPostedZombieHypnotized[10000] = {};

void EventHandler::UpdateZombies()
{
	if (!Address)
	{
		if(ZombieList.size())
			ZombieList.clear();
		return;
	}
	std::vector<Zombie*> now;
	now.clear();
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		now.push_back(new Zombie(i));
	for (int i = 0; i < now.size(); i++)
	{
		Zombie* x = now[i];
		if (x->NotExist && !isPostedZombieDead[x->Index])
		{
			isPostedZombieDead[x->Index] = true;
			InvokeZombieDeadEvent(x);
		}
	}
	now = GetAllZombies();
	int nown = now.size();
	int lastn = ZombieList.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Zombie* x = now[i];
		
		for(int j=0;j<lastn;j++)
			if (x->BaseAddress == ZombieList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in last, spawns
			InvokeZombieSpawnEvent(x);
		}

		if (x->Hypnotized)
		{
			if (!isPostedZombieHypnotized[x->Index])
			{
				isPostedZombieHypnotized[x->Index] = true;
				InvokeZombieHypnotizedEvent(x);
			}
		}
	}
	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Zombie* x = ZombieList[i];
		for(int j=0;j<nown;j++)
			if (x->BaseAddress == now[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in now, remove
			InvokeZombieRemoveEvent(x);
		}
	}
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Zombie* x = now[i];

		for (int j = 0; j < lastn; j++)
			if (x->BaseAddress == ZombieList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in last, spawns
			InvokeZombieSpawnEvent(x);
		}
	}
	ZombieList.clear();
	ZombieList = now;
}
void EventHandler::RegisterZombieSpawnEvent(bool function(Zombie*), int level)
{
	if (level == Event_Low)
		FunctionZombieSpawnEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionZombieSpawnEventMid.push_back(function);
	else if (level == Event_High)
		FunctionZombieSpawnEventHigh.push_back(function);
}
void EventHandler::RegisterZombieRemoveEvent(bool function(Zombie*), int level)
{
	if (level == Event_Low)
		FunctionZombieRemoveEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionZombieRemoveEventMid.push_back(function);
	else if (level == Event_High)
		FunctionZombieRemoveEventHigh.push_back(function);
}
void EventHandler::RegisterZombieDeadEvent(bool function(Zombie*), int level)
{
	if (level == Event_Low)
		FunctionZombieDeadEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionZombieDeadEventMid.push_back(function);
	else if (level == Event_High)
		FunctionZombieDeadEventHigh.push_back(function);
}

void EventHandler::RegisterZombieHypnotizedEvent(bool function(Zombie*), int level)
{
	if (level == Event_Low)
		FunctionZombieHypnotizedEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionZombieHypnotizedEventMid.push_back(function);
	else if (level == Event_High)
		FunctionZombieHypnotizedEventHigh.push_back(function);
}
