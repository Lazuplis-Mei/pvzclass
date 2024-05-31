#include "pvzclass.h"
#include "Events/Events.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	PVZ::Memory::immediateExecute = true;
	PVZ::Memory::InjectDll("pvzdll.dll");
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();

	CoinCreateEvent();
	CoinCollectEvent();
	CoinRemoveEvent();
	DrawUITopEvent();
	PlantCreateEvent();
	PlantReloadEvent();
	PlantShootEvent();
	PlantRemoveEvent();
	PeaOnFireEvent();
	ProjectileCreateEvent();
	ProjectileHitZombieEvent();
	ProjectileRemoveEvent();
	UpdateGameObjectsEvent();
	SeedCardClickEvent();
	ZombieBlastEvent();
	ZombieButterEvent();
	ZombieDecelerateEvent();
	ZombieEatEvent();
	ZombieFrozeEvent();
	ZombieHitEvent();
	ZombieHypnotizeEvent();
	ZombieRemoveEvent();
	system("pause");

	PVZ::QuitPVZ();
	return 0;
}
