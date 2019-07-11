#include "pvzclass.h"
#include <iostream>
#include <time.h> 

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

		if (pPVZ->BaseAddress)
		{
			PVZ::Zombie* zombie = GetFirstZombie();
			if (zombie)
			{
				zombie->SetAnimation("anim_idle", APA_LOOP);//APA_LOOP或APA_ONCE_DISAPPEAR或APA_ONCE_STOP
			}
		}
		delete pPVZ;
	}
	return 0;
}
