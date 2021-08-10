#include "events.h"

typedef PVZ::Zombie Zombie;

std::vector<SPT<Zombie>> EventHandler::GetAllZombies()
{
	std::vector<SPT<Zombie>> rt;
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0x90, 0xEC + 0x15C * i))
			rt.push_back(MKS<Zombie>(i));
	return rt;
}

std::map<int,bool> isPostedZombieDead;
std::map<int, bool> isPostedZombieHypnotized;

void EventHandler::UpdateZombies()
{
	if (!Address)
	{
		if(ZombieList.size())
			ZombieList.clear();
		return;
	}
	std::vector<SPT<Zombie>> now;
	now.clear();
	int n = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0x94);
	for (int i = 0; i < n; i++)
		now.push_back(MKS<Zombie>(i));
	for (int i = 0; i < now.size(); i++)
	{
		Zombie* zombie = now[i].get();
		if ((zombie->State==ZombieState::DYING|| zombie->State == ZombieState::DYING_FROM_INSTANT_KILL || zombie->State == ZombieState::DYING_FROM_LAWNMOWER) && !isPostedZombieDead[zombie->Index])
		{
			isPostedZombieDead[zombie->Index] = true;
			InvokeEvent(new EventZombieDead(zombie),true);
		}
	}
	now = GetAllZombies();
	int nown = now.size();
	int lastn = ZombieList.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Zombie* zombie = now[i].get();

		for(int j=0;j<lastn;j++)
			if (zombie->BaseAddress == ZombieList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in last, spawns
			InvokeEvent(new EventZombieSpawn(zombie),true);
		}

		if (zombie->Hypnotized)
		{
			if (!isPostedZombieHypnotized[zombie->Index])
			{
				isPostedZombieHypnotized[zombie->Index] = true;
				InvokeEvent(new EventZombieHypnotized(zombie),true);
			}
		}
	}
	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Zombie* zombie = ZombieList[i].get();
		for(int j=0;j<nown;j++)
			if (zombie->BaseAddress == now[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			//didn't found x in now, remove
			InvokeEvent(new EventZombieRemove(zombie),true);
		}
	}
	ZombieList.clear();
	ZombieList = now;
}