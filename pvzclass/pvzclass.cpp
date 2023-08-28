#include "pvzclass.h"
#include "HookEvents/ZombieEatEvent.h"
#include <iostream>

using namespace std;

void listener0(shared_ptr<PVZ::Zombie> zombie, shared_ptr<PVZ::Plant> plant)
{
	cout << ZombieType::ToString(zombie->Type) << " 啃食了 " << PlantType::ToString(plant->Type) << endl;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	ZombieEatEvent e;
	e.start();
	e.addListener(listener0);

	while (true)
	{
		e.run();
	}

	e.end();
	delete pvz;
	return 0;
}
