#include "pvzclass.h"
#include "DebugEvents/ZombieEatEvent.h"
#include "DebugEvents/ZombieHitEvent.h"
#include <iostream>

using namespace std;

void listener0(shared_ptr<PVZ::Zombie> zombie, shared_ptr<PVZ::Plant> plant)
{
	cout << ZombieType::ToString(zombie->Type) << " 啃食了 ";
}

void listener1(shared_ptr<PVZ::Zombie> zombie, shared_ptr<PVZ::Plant> plant)
{
	cout << PlantType::ToString(plant->Type) << endl;
}

int listener2(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << ZombieType::ToString(zombie->Type) << " 受到了 ";
	return amount * 2;
}

int listener3(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
	cout << amount << " 点伤害，类型为：" << DamageType::ToString(type) << endl;
	return amount;
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	DEBUG_EVENT debugEvent;
	eventHandlerStart(debugEvent);
	CONTEXT context;
	HANDLE hThread;
	ZombieEatEvent e1;
	e1.start();
	e1.addListener(listener0);
	e1.addListener(listener1);
	ZombieHitEvent e2;
	e2.start();
	e2.addListener(listener2);
	e2.addListener(listener3);

	while (true)
	{
		eventHandlerRun(debugEvent, context, hThread, -1);
		if (hThread != NULL)
		{
			e1.handle(debugEvent, context, hThread);
			e2.handle(debugEvent, context, hThread);
		}
		Sleep(10);
	}

	e1.end();
	e2.end();
	eventHandlerStop();
	delete pvz;
	return 0;
}
