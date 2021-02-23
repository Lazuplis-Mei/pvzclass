#include "events.h"
#include <vector>
#include <iostream>

std::vector<Projectile*> EventHandler::GetAllProjectiles()
{
	std::vector<Projectile*> rt;
	int maxnum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0xC8, 0x50 + 0x94 * i))
			rt.push_back(new PVZ::Projectile(i));
	return rt;
}


std::vector<bool> lastDead;

void EventHandler::UpdateProjectiles()
{
	if (!Address)
	{
		if (ProjectileList.size())
			ProjectileList.clear();
		return;
	}
	std::vector<Projectile*> list = GetAllProjectiles();
	int nown = list.size();
	int lastn = ProjectileList.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Projectile* x = list[i];
		for (int j = 0; j < lastn; j++)
			if (x->BaseAddress == ProjectileList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
			InvokeEvent(new EventProjectileFire(x),true);
	}

	std::vector<Projectile*> lpros;
	int maxnum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
		lpros.push_back(new PVZ::Projectile(i));

	for (int i = 0; i < lpros.size(); i++)
	{
		if (lastDead.size()<= lpros[i]->Index) {
			while (lastDead.size() <= lpros[i]->Index + 3) {
				lastDead.push_back(false);
			}
		}
		if (lpros[i] != NULL)
		{
			if (lpros[i]->NotExist&&!lastDead[lpros[i]->Index])
			{
				lastDead[lpros[i]->Index] = true;
				std::vector<Zombie*> zombies = GetAllZombies();
				int minn=9999999;
				Zombie* x=zombies[0];
				for (int j = 0; j < zombies.size(); j++) {
					if (abs(zombies[j]->X - lpros[i]->X) + abs(zombies[j]->Y - lpros[i]->Y)<minn) {
						x = zombies[j];
						minn = abs(zombies[j]->X - lpros[i]->X) + abs(zombies[j]->Y - lpros[i]->Y);
					}
				}
				if (minn!=9999999)
				{
					InvokeEvent(new EventZombieDamage(x, lpros[i]), true);
				}
			}
			else if(!lpros[i]->NotExist){
				if (lastDead.size() <= lpros[i]->Index) {
					while (lastDead.size() <= lpros[i]->Index + 3) {
						lastDead.push_back(false);
					}
				}
				lastDead[lpros[i]->Index] = false;
			}
		}
	}
	

	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Projectile* x = ProjectileList[i];
		for (int j = 0; j < nown; j++)
			if (x->BaseAddress == list[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
			InvokeEvent(new EventProjectileRemove(x),true);
	}
	ProjectileList.clear();
	ProjectileList = list;
}
