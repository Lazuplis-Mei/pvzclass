#include "pvzclass.h"
#include "DebugEvents/EventHandler.h"
#include "DebugEvents/ZombieEatEvent.h"
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

	DEBUG_EVENT debugEvent;
	eventHandlerStart(debugEvent);
	CONTEXT context;
	HANDLE hThread;
	ZombieEatEvent e;
	cout << 1;
	e.start();
	cout << 2;
	e.addListener(listener0);

	while (true)
	{
		cout << 3;
		hThread = eventHandlerRun(debugEvent, context, -1);
		cout << 4;
		if (hThread != NULL)
		{
			cout << 5;
			e.handle(debugEvent, context, hThread);
		}
	}

	e.end();
	eventHandlerStop();
	delete pvz;
	return 0;
}
