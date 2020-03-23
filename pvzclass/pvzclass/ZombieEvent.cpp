#include "events.h"

typedef PVZ::Zombie Zombie;

std::vector<Zombie*> EventHandler::getAllZombies()
{
	std::vector<Zombie*> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt.push_back(new Zombie(i));
	return rt;
}
void EventHandler::invokeZombieSpawnEvent(Zombie* zombie)
{
	int lim = functionZombieSpawnEvent.size();
	for (int i = 0; i < lim; i++)
		functionZombieSpawnEvent[i](zombie);
}
void EventHandler::invokeZombieRemoveEvent(Zombie* zombie)
{
	int lim = functionZombieRemoveEvent.size();
	for (int i = 0; i < lim; i++)
		functionZombieRemoveEvent[i](zombie);
}
void EventHandler::updateZombies()
{
	if (!address)
	{
		if(zombielist.size())
			zombielist.clear();
		return;
	}
	std::vector<Zombie*> now = getAllZombies();
	int nown = now.size();
	int lastn = zombielist.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Zombie* x = now[i];
		for(int j=0;j<lastn;j++)
			if (x->BaseAddress == zombielist[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in last, spawns
			invokeZombieSpawnEvent(x);
		}
	}
	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Zombie* x = zombielist[i];
		for(int j=0;j<nown;j++)
			if (x->BaseAddress == now[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in now, remove
			invokeZombieRemoveEvent(x);
		}
	}
	zombielist.clear();
	zombielist = now;
}
void EventHandler::registerZombieSpawnEvent(void function(Zombie*))
{
	functionZombieSpawnEvent.push_back(function);
}
void EventHandler::registerZombieRemoveEvent(void function(Zombie*))
{
	functionZombieRemoveEvent.push_back(function);
}