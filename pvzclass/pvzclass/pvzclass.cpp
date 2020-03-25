#include "pvzclass.h"
#include <iostream>
#include "events.h"

using namespace std;
void onPlant(PVZ::Plant* plant)
{
	//...
	cout << plant->Row << " " << plant->Column << " " << ToString(plant->Type) << endl;
	//plant->Type = PlantType::Cattail;
}
void onOpen()
{
	cout << "OPEN" << endl;
}
void onClose()
{
	cout << "CLOSE" << endl;
}
void onWave(int wave)
{
	cout << wave << endl;
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
	e.RegisterPlantPlantEvent(onPlant);
	e.RegisterLevelOpenEvent(onOpen);
	e.RegisterLevelCloseEvent(onClose);
	e.RegisterLevelWaveEvent(onWave);
	while (pvz->BaseAddress)
	{
		//cerr << pvz->WaveCount << " " << pvz->RefreshedWave << endl;
		e.Run();
		Sleep(10);
	}

	//EventHandler end
	delete pvz;
	return 0;
}