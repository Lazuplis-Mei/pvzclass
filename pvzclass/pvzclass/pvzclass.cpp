#include "pvzclass.h"
#include "events.h"
#include <iostream>
using namespace std;

void plant(PVZ::Plant e)
{
	cout << "found Plant on " << e.Row << " " << e.Column << " " << ToString(e.Type) << endl;
}
void remove(PVZ::Plant e)
{
	cout << "found Remove on " << e.Row << " " << e.Column << " " << ToString(e.Type) << endl;
}
void upgrade(PVZ::Plant e)
{
	cout << "found Upgrade on " << e.Row << " " << e.Column << " " << ToString(e.Type) << endl;
}
int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid)
		return 1;
	cout << pid << endl;
	PVZ* pvz = new PVZ(pid);
	cout << pvz->BaseAddress << endl;
	if (!pvz->BaseAddress)
		return 2;
	EventHandler e(pvz);
	e.registerPlantPlantEvent(plant);
	e.registerPlantRemoveEvent(remove);
	e.registerPlantUpgradeEvent(upgrade);
	while (1)
		e.run();
	delete pvz;
	return 0;
}