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

		//enable backgroung running
		PVZ::Memory::WriteMemory<byte>(0x54EBA8, 112);

		if (PVZ::PVZ_BASE && pPVZ->BaseAddress)
		{			
			PVZ::Zombie* zombies[20];
			int len = pPVZ->GetAllZombies(zombies);
			for (int i = 0; i < len; i++)
			{
				cout << enumstring::ZombieType[zombies[i]->Type + 1] << endl;
				zombies[i]->Blast();
			}			
		}
		delete pPVZ;
	}
	return 0;
}
