#include<cstdio>
#include "pvzclass.h"
#include "events.h"
#include "Injectors.h"

PVZ* pPVZ;

byte asmZombieHurt[7]
{
	MOV_PTR_ADDR_ESI(0),
	RET
};

void onPlantPlant(EventPlantPlant* e,PVZ *pvz)
{
	Creater::CreateCoin(CoinType::MiniSun,e->plant->X,e->plant->Y,CoinMotionType::Product);
	return;
}

void onPlantPlant2(EventPlantPlant* e, PVZ* pvz)
{
	if (e->plant->Column == 0)
		pvz->Sun >>= 1,e->CancleState = true;
	return;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid)
		return(-2);
	std::printf("%u\n",pid);
	pPVZ = new PVZ(pid);
	EventHandler EvntHdl(pPVZ);
	Injector InjZombieHurt(0x5317C9, 5);
	
	SETARG(asmZombieHurt, 2) = InjZombieHurt.InjectPos + 0x3C0; 
	InjZombieHurt.Insert(asmZombieHurt, 7);
	EvntHdl.RegistryListeners(onPlantPlant);
	EvntHdl.RegistryListeners(onPlantPlant2, Event_High);
	
	while (PVZBASEADDRESS)
	{
		EvntHdl.Run();
		if (PVZ::Memory::ReadMemory<int>(InjZombieHurt.InjectPos + 0x3C0))
		{
			SPT<PVZ::Zombie> tmpZ = MKS<PVZ::Zombie>(PVZ::Memory::ReadMemory<int>(InjZombieHurt.InjectPos + 0x3C0));
			std::printf("%s\n", ZombieType::ToString(tmpZ->Type));
			PVZ::Memory::WriteMemory<int>(InjZombieHurt.InjectPos + 0x3C0, 0);
		}
	}
	
	InjZombieHurt.Remove();
	delete(pPVZ);
	return(0);
}