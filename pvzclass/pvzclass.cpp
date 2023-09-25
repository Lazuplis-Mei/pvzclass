#include "pvzclass.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	PVZ::Memory::WriteMemory<BYTE>(0x45EF2C, 0xEB);
	
	auto portal1 = Creator::CreatePortal(1, 4, 1);

	while (true)
	{
		shared_ptr<PVZ::Projectile> projs[256];
		int num = pvz->GetAllProjectile(projs);
		for (int i = 0; i < num; i++)
		{
			if (portal1->isProjectileIn(projs[i]))
			{
				auto p = Creator::CreateProjectile(ProjectileType::Pea, projs[i]->Row, portal1->getProjectileOutX());
				projs[i]->Remove();
			}
		}

		shared_ptr<PVZ::Zombie> zombies[256];
		num = pvz->GetAllZombies(zombies);
		for (int i = 0; i < num; i++)
		{
			if (portal1->isZombieIn(zombies[i]))
			{
				auto z = Creator::CreateZombie(ZombieType::Zombie, zombies[i]->Row, 10);
				z->X = portal1->getZombieOutX();
				zombies[i]->Remove();
			}
		}

	}

	delete pvz;
	return 0;
}
