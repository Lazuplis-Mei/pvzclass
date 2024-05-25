#include "pvzclass.h"
#include "Events/CoinCollectEvent.h"
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
	cout << PVZ::Memory::InjectDll("pvzdll.dll") << endl;
	cout << PVZ::Memory::InvokeDllProc("init") << endl;
	EnableBackgroundRunning();

	CoinCollectEvent e = CoinCollectEvent();
	system("pause");
	e.end();

	PVZ::QuitPVZ();
	return 0;
}
