#include "ProcessOpener.h"
#include "PVZ.h"
#include <iostream>
#include "Creaters.h"
#include "Extensions.h"

using namespace std;


int main()
{

	DWORD pid = ProcessOpener::Open();

	if (pid)
	{
		PVZ* pPVZ = new PVZ(pid);
		PVZ::Mouse* pMouse = pPVZ->GetMouse();

		EnableBackgroundRunning();
		
		PVZ::Zombie* zombie = CreateZombie(ZombieType::FootballZombie, 2, 3);
		zombie->Size = 2;

		delete pPVZ;
	}
	return 0;
}
