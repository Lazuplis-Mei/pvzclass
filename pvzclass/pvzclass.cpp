#include "pvzclass.h"
#include "Events/CoinCollectEvent.h"
#include "Events/CoinCreateEvent.h"
#include "Events/CoinRemoveEvent.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	PVZ::Memory::immediateExecute = true;
	PVZ::Memory::InjectDll("pvzdll.dll");
	PVZ::Memory::InvokeDllProc("init");
	EnableBackgroundRunning();

	auto e1 = CoinCollectEvent();
	auto e2 = CoinCreateEvent();
	auto e3 = CoinRemoveEvent();
	system("pause");
	e1.end();
	e2.end();
	e3.end();

	PVZ::QuitPVZ();
	return 0;
}
