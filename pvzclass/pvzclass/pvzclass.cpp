#include "pvzclass.h"
#include <iostream>

using namespace std;


PVZ::Zombie* GetFirstZombie()
{
	int len = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x94);
	for (int i = 0; i < len; i++)
	{
		PVZ::Zombie* zombie = new PVZ::Zombie(i);
		if (!zombie->NotExist && zombie->NotDying)return zombie;
	}
	return NULL;
}

int main()
{

	DWORD pid = ProcessOpener::Open();
	
	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);
		PVZ::Mouse* pMouse = pPVZ->GetMouse();

		EnableBackgroundRunning();
		Creater::AsmInit();
		while (pPVZ->BaseAddress)
		{
			PVZ::Projectile* projectiles[10];
			for (int i = 0; i < 10; i++)
				projectiles[i] = Creater::CreateProjectile(ProjectileType::Star, 400, 300, 36 * i, 1);
			
			Sleep(1000);
			
			PVZ::Zombie* zombie = GetFirstZombie();
			if (zombie)
			{
				for (int i = 0; i < 10; i++)
				{
					CollisionBox cbox;
					zombie->GetCollision(&cbox);
					float dx = zombie->X + cbox.X + cbox.Width / 2 - projectiles[i]->X;
					float dy = zombie->Y + cbox.Y + cbox.Height / 2 - projectiles[i]->Y;
					projectiles[i]->XSpeed = dx / 50.0f;
					projectiles[i]->YSpeed = dx / 50.0f * dy / dx;
				}
			}
		}

		delete pPVZ;
	}
	return 0;
}
