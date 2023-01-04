#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;

class MyZombie: public PVZ::Zombie
{
public:
	static const int MemSize = 0x16C;
	MyZombie(int indexoraddress): PVZ::Zombie(indexoraddress)
	{
		if (indexoraddress > 1024)
			BaseAddress = indexoraddress;
		else
			BaseAddress = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0xAC) + indexoraddress * MemSize;
#if _DEBUG
		DebugType = Type;
#endif
	}
};

void OnDeath(EventZombieDead* e, PVZ* pvz)
{
	e->CancleState = true;
	std::cout << endl << ZombieState::ToString(e->zombie->State);
}

void OnDeath2(EventZombieDead* e, PVZ* pvz)
{
	std::cout << endl << "2 "<< e->zombie->Index;
}

void OnPlantDead(EventPlantDead* e, PVZ* pvz)
{
	// Creator::CreatePlant(PlantType::Doomshroon, 3, 3);
	std::cout << e->last_pos.first << " " << e->last_pos.second << std::endl;
	Creator::CreateCoin(CoinType::NormalSun, e->last_pos.first, e->last_pos.second, CoinMotionType::Spray);
}

void OnPlantDamage(EventPlantDamage* e, PVZ* pvz)
{
	PVZ::Plant* plant = e->plant;
	if (plant->Row == e->zombie->Row)
	{
		plant->Smash();
		e->zombie->Hypnotize();
		e->zombie->Froze(1000);
		e->zombie->Decelerate(5000);
	}
}

void OnPotatoMineSproutOut(EventPlantPotatoMineSproutOuted* e, PVZ* pvz) {
	e->plant->Type = PlantType::FlowerPot;
	std::cout << "!";
}

void OnPoleVaultingJumping(EventZombiePoleVaultingJumped* e, PVZ* pvz) {
	e->zombie->Type = ZombieType::ConeheadZombie;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid)
		return 1;
	cout << pid << endl;

	PVZ* pvz = new PVZ(pid);
	MyZombie::SetMemSize(0x15C, 2048);
	cout << pvz->BaseAddress << endl;
	if (!pvz->BaseAddress)
		return 2;

	pvz->Sun = 8000;

	//EventHandler 的代码留在这里只是为了演示它的用法。
	//若要深入了解，请把 SetMemSize() 删掉。
	
	//EventHandler start
	EventHandler e(pvz);
	e.RegistryListeners(OnDeath, Event_High);
	e.RegistryListeners(OnDeath2, Event_Low);
	e.RegistryListeners(OnPlantDead);
	e.RegistryListeners(OnPlantDamage);
	e.RegistryListeners(OnPotatoMineSproutOut);
	e.RegistryListeners(OnPoleVaultingJumping);
	while (pvz->BaseAddress)
	{
		//cerr << pvz->WaveCount << " " << pvz->RefreshedWave << endl;
		e.Run();
	}

	//EventHandler end
	delete pvz;
	return 0;
}
