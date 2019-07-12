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
			Creater::CreateEffect(4, 100.0f, 100.0f);
		}
		delete pPVZ;
	}
	return 0;
}
