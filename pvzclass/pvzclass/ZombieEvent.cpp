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
std::vector<Projectile*> EventHandler::GetAllProjectiles()
{
	return std::vector<Projectile*>();
}
void EventHandler::InvokeZombieSpawnEvent(Zombie* zombie)
{
	int lim = FunctionZombieSpawnEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionZombieSpawnEvent[i](zombie);
}
void EventHandler::InvokeZombieRemoveEvent(Zombie* zombie)
{
	int lim = FunctionZombieRemoveEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionZombieRemoveEvent[i](zombie);
}
void EventHandler::UpdateZombies()
{
	if (!Address)
	{
		if(ZombieList.size())
			ZombieList.clear();
		return;
	}
	std::vector<Zombie*> now = GetAllZombies();
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
	ZombieList.clear();
	ZombieList = now;
}
void EventHandler::RegisterZombieSpawnEvent(void function(Zombie*))
{
	FunctionZombieSpawnEvent.push_back(function);
}
void EventHandler::RegisterZombieRemoveEvent(void function(Zombie*))
{
	FunctionZombieRemoveEvent.push_back(function);
}