#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;
bool OnDeath(Zombie* zombie)
{
	std::cout << endl << zombie->Index;
	return true;
}

bool OnDeath2(Zombie* zombie)
{
	std::cout << endl <<"2"<< zombie->Index ;
	return true;
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
	e.RegisterZombieDeadEvent(OnDeath, Event_High);
	e.RegisterZombieDeadEvent(OnDeath2, Event_Low);
	while (pvz->BaseAddress)
	{
		//cerr << pvz->WaveCount << " " << pvz->RefreshedWave << endl;
		e.Run();
	}

	//EventHandler end
	delete pvz;
	return 0;
}