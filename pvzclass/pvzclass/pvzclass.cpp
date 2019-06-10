#include "ProcessOpener.h"
#include "PVZ.h"
#include <iostream>
using namespace std;

#define ENUMSTRING
#undef VNAME
#undef IDENTIFIER
#include "Enums.h"


int main()
{
	DWORD pid = ProcessOpener::Open();

	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);
		PVZ::Mouse* pMouse = pPVZ->GetMouse();
		//enable backgroung running
		PVZ::Memory::WriteMemory<byte>(0x54EBA8, 112);

		while (PVZ::PVZ_BASE && pPVZ->BaseAddress)
		{
			
			PVZ::Zombie* zombies[30];
			int len = pPVZ->GetAllZombies(zombies);
			for (int i = 0; i < len; i++)
			{
				if (zombies[i]->ExistedTime > 50)
				{
					CollisionBox cbox;
					zombies[i]->GetCollision(&cbox);
					int x = zombies[i]->ImageX + cbox.Width / 2;
					int y = zombies[i]->ImageY + cbox.Height / 2;
					pMouse->MoveTo(x, y);
					pMouse->GameClick(x, y);
					Sleep(100);
				}
			}
			PVZ::Coin* coins[40];
			len = pPVZ->GetAllCoins(coins);
			for (int i = 0; i < len; i++)
			{
				if (!coins[i]->Collected) 
				{
					CollisionBox cbox;
					coins[i]->GetCollision(&cbox);
					int x = coins[i]->X + cbox.Width / 2;
					int y = coins[i]->Y + cbox.Height / 2;
					pMouse->MoveTo(x, y);
					pMouse->GameClick(x, y);
					Sleep(100);
				}
			}
		}
		delete pPVZ;
	}
	return 0;
}
