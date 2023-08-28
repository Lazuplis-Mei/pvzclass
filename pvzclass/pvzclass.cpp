#include "pvzclass.h"
#include "HookEvents/PlantShootEvent.h"
#include <iostream>

using namespace std;

void listener0(shared_ptr<PVZ::Plant> plant, shared_ptr<PVZ::Projectile> projectile)
{
	cout << PlantType::ToString(plant->Type) << " 发射了 " << ProjectileType::ToString(projectile->Type) << endl;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	PlantShootEvent e;
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
