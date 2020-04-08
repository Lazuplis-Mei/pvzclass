#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;
void OnDeath(Zombie* zombie)
{
	std::cout << zombie->Index<<endl;
}

int main()
{
	DWORD pid = ProcessOpener::Open();

	if (!pid)
		return 1;
	cout << pid << endl;
	PVZ* pvz = new PVZ(pid);

	cout << pvz->BaseAddress << endl;
	//if (!pvz->BaseAddress)
	//	return 2;
	//EventHandler start
	EventHandler e(pvz);
	e.RegisterZombieDeadEvent(OnDeath);
	while (pvz->BaseAddress)
	{
		//cerr << pvz->WaveCount << " " << pvz->RefreshedWave << endl;
		e.Run();
	}

	//EventHandler end
	delete pvz;
	return 0;
}