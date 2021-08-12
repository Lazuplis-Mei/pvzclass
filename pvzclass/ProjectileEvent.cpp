#include "events.h"
#include <vector>
#include <iostream>

std::vector<SPT<Projectile>> EventHandler::GetAllProjectiles()
{
	std::vector<SPT<Projectile>> rt;
	int maxnum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0xC8, 0x50 + 0x94 * i))
			rt.push_back(MKS<PVZ::Projectile>(i));
	return rt;
}


std::map<int, bool> lastDead;

void EventHandler::UpdateProjectiles()
{
	if (!Address)
	{
		if (ProjectileList.size())
			ProjectileList.clear();
		if (lastDead.size())
			lastDead.clear();
		return;
	}
	std::vector<SPT<Projectile>> list = GetAllProjectiles();
	int nown = list.size();
	int lastn = ProjectileList.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Projectile* proj = list[i].get();
		for (int j = 0; j < lastn; j++)
			if (proj->BaseAddress == ProjectileList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok) {
			std::vector<SPT<Plant>> plants = GetAllPlants();
			int minn = INT_MAX;
			Plant* plant;
			if (plants.size())
			{
				plant = plants[0].get();
				for (int j = 0; j < plants.size(); j++) {
					if (abs(plants[j]->X - proj->X) + abs(plants[j]->Y - proj->Y) < minn) {
						plant = plants[j].get();
						minn = abs(plants[j]->X - proj->X) + abs(plants[j]->Y - proj->Y);
					}
				}
				if (minn != INT_MAX)
				{
					InvokeEvent(new EventProjectileFire(proj, plant), true);
				}
				else {
					InvokeEvent(new EventProjectileSpawn(proj), true);
				}
			}
		}
	}

	std::vector<Projectile*> lpros;
	int maxnum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
		lpros.push_back(new PVZ::Projectile(i));

	for (int i = 0; i < lpros.size(); i++)
	{
		if (lpros[i]->NotExist&&!lastDead[lpros[i]->Index])
		{
			lastDead[lpros[i]->Index] = true;
			std::vector<SPT<Zombie>> zombies = GetAllZombies();
			int minn = INT_MAX;
			Zombie* zombie;
			if (zombies.size())
			{
				zombie = zombies[0].get();
				for (int j = 0; j < zombies.size(); j++) {
					if (abs(zombies[j]->X - lpros[i]->X) + abs(zombies[j]->Y - lpros[i]->Y) < minn) {
						zombie = zombies[j].get();
						minn = abs(zombies[j]->X - lpros[i]->X) + abs(zombies[j]->Y - lpros[i]->Y);
					}
				}
				if (minn != INT_MAX)
				{
					InvokeEvent(new EventZombieDamage(zombie, lpros[i]), true);
				}
			}	
		}
		else if(!lpros[i]->NotExist){
			lastDead[lpros[i]->Index] = false;
		}
	}
	

	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Projectile* proj = ProjectileList[i].get();
		for (int j = 0; j < nown; j++)
			if (proj->BaseAddress == list[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
			InvokeEvent(new EventProjectileRemove(proj),true);
	}
	ProjectileList.clear();
	ProjectileList = list;
}
