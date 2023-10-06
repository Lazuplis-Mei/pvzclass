#include "pvzclass.h"
#include <iostream>
#include <thread>

using namespace std;

PVZ* pvz;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	pvz = new PVZ(pid);

	auto cardslot = pvz->GetCardSlot();
	auto seedcard = cardslot->GetCard(0);

	while (1)
	{
		int time = rand() % 1000;
		cout << time << endl;
		seedcard->EnterCoolDown(time);
		Sleep(time * 11);
	}

	delete pvz;
	return 0;
}
