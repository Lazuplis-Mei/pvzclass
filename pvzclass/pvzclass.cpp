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

	auto zombie = Creator::CreateZombie(ZombieType::Zombie, 2, 10);
	Sleep(5000);
	zombie->HitBody(300);
	zombie = Creator::CreateZombie(ZombieType::FootballZombie, 2, 10);
	Sleep(5000);
	zombie->HitBody(300);
	zombie = Creator::CreateZombie(ZombieType::LadderZombie, 2, 10);
	Sleep(5000);
	zombie->HitBody(300);

	delete pvz;
	return 0;
}
