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
			InvokeEvent(new EventZombieDead(x),true);
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
			InvokeEvent(new EventZombieSpawn(x),true);
		}

		if (x->Hypnotized)
		{
			if (!isPostedZombieHypnotized[x->Index])
			{
				isPostedZombieHypnotized[x->Index] = true;
				InvokeEvent(new EventZombieHypnotized(x),true);
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
			InvokeEvent(new EventZombieRemove(x),true);
		}
	}
	ZombieList.clear();
	ZombieList = now;
}