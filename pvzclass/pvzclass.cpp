#include "pvzclass.h"
#include "Events/Events.h"
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
	DisableInitialLawnmover();
	DisableIceLevelFailSound();

	system("pause");
	DialogButtonDepressEvent();
	Draw::PString str = Draw::ToString("Hello, world!\0");
	Sexy::PDialog dialog = Sexy::MakeDialog(1, str, str, str, 0, 100);
	Sexy::AddToManager(dialog);
	system("pause");
	Sexy::RemoveFromManager(dialog);
	Sexy::FreeWidget(dialog);

	PVZ::QuitPVZ();
	return 0;
}
