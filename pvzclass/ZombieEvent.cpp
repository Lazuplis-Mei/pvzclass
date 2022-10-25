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

std::map<int, bool> isPostedZombieDead;
std::map<int, bool> isPostedZombieHypnotized;
std::map<int, bool> isNewspaperDestroyed;
std::map<int, bool> isNewspaperZombieAngried;
std::map<int, bool> isPoleVaultingZombieJumped;
std::map<int, bool> isPoleVaultingZombieWalked;

void EventHandler::UpdateZombies()
{
	if (!Address)
	{
		if(ZombieList.size())
			ZombieList.clear();
		if (isPostedZombieDead.size())
			isPostedZombieDead.clear();
		if (isPostedZombieHypnotized.size())
			isPostedZombieHypnotized.clear();
		if (isNewspaperDestroyed.size())
			isNewspaperDestroyed.clear();
		if (isNewspaperZombieAngried.size())
			isNewspaperZombieAngried.clear();
		if (isPoleVaultingZombieJumped.size())
			isPoleVaultingZombieJumped.clear();
		if (isPoleVaultingZombieWalked.size())
			isPoleVaultingZombieWalked.clear();
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
	for (int i = 0, j = 0; i < nown; i++)
	{
		bool ok = 1;
		Zombie* zombie = now[i].get();

		for(;j < lastn ; j++)
			if (ZombieList[j]->BaseAddress >= zombie->BaseAddress)
				break;
		if (j == lastn || ZombieList[j]->BaseAddress != zombie->BaseAddress)
		{
			//didn't found x in last, spawns
			InvokeEvent(new EventZombieSpawn(zombie),true);
		}

		if (zombie->Hypnotized && !isPostedZombieHypnotized[zombie->Index])
		{
			isPostedZombieHypnotized[zombie->Index] = true;
			InvokeEvent(new EventZombieHypnotized(zombie),true);
		}
		if (zombie->Type == ZombieType::NewspaperZombie && zombie->State == ZombieState::NEWSPAPER_DESTORYED && ! isNewspaperDestroyed[zombie->Index]) {
			isNewspaperDestroyed[zombie->Index] = true;
			InvokeEvent(new EventZombieNewspaperDestoryed(zombie), true);
		}
		if (zombie->Type == ZombieType::NewspaperZombie && zombie->State == ZombieState::NEWSPAPER_RUNNING && !isNewspaperZombieAngried[zombie->Index]) {
			isNewspaperZombieAngried[zombie->Index] = true;
			InvokeEvent(new EventZombieNewspaperAngried(zombie), true);
		}
		if (zombie->Type == ZombieType::PoleVaultingZombie && zombie->State == ZombieState::POLE_VALUTING_JUMPPING && !isPoleVaultingZombieJumped[zombie->Index]) {
			isPoleVaultingZombieJumped[zombie->Index] = true;
			InvokeEvent(new EventZombiePoleVaultingJumped(zombie), true);
		}
		if (zombie->Type == ZombieType::PoleVaultingZombie && zombie->State == ZombieState::POLE_VAULTING_WALKING && !isPoleVaultingZombieWalked[zombie->Index]) {
			isPoleVaultingZombieWalked[zombie->Index] = true;
			InvokeEvent(new EventZombiePoleVaultingWalked(zombie), true);
		}
	}
	for (int i = 0, j = 0; i < lastn; i++)
	{
		bool ok = 1;
		Zombie* zombie = ZombieList[i].get();
		for (; j < nown; j++)
			if (now[j]->BaseAddress >= zombie->BaseAddress)
				break;
		if (j == nown || now[j]->BaseAddress != zombie->BaseAddress)
		{
			//didn't found x in now, remove
			InvokeEvent(new EventZombieRemove(zombie),true);
		}
	}
	ZombieList.clear();
	ZombieList = now;
}