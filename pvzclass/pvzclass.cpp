#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;
void OnDeath(Event* e)
{
	e->CancleState = true;
	//std::cout << endl << ((EventZombieDead*)e)->zombie->Index;
	std::cout << endl << ZombieState::ToString(((EventZombieDead*)e)->zombie->State);
}

void OnDeath2(Event* e)
{
	std::cout << endl <<"2 "<< ((EventZombieDead*)e)->zombie->Index;
}

void OnPlantDead(Event* e)
{
	Creater::CreatePlant(PlantType::Doomshroon, 3, 3);
}

void OnPlantDamage(Event* e)
{
	((EventPlantDamage*)e)->zombie->Hypnotized = true;
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
	e.RegistryListeners("ZombieDead",OnDeath, Event_High);
	e.RegistryListeners("ZombieDead",OnDeath2, Event_Low);
	e.RegistryListeners("PlantDead", OnPlantDead);
	e.RegistryListeners("PlantDamage", OnPlantDamage);
	while (pvz->BaseAddress)
	{
		//cerr << pvz->WaveCount << " " << pvz->RefreshedWave << endl;
		e.Run();
	}

	//EventHandler end
	delete pvz;
	return 0;
}