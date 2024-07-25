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
	DialogDrawEvent();
	system("pause");
	Sexy::EditListener listener;
	Sexy::PEditListener plistener = Sexy::MakeEditListener(&listener);
	Draw::PString str = Draw::ToString("Hello, world!\0");
	Sexy::PDialog dialog = Sexy::MakeDialog(1, str, str, str, 0, 100);
	PVZ::Memory::WriteMemory<DWORD>(0x702000, dialog);
	Sexy::PEdit edit = Sexy::MakeEdit(dialog, plistener);
	PVZ::Memory::WriteMemory<DWORD>(0x702004, edit);
	Sexy::ResizeWidget(edit, 100, 50, 100, 50);
	Sexy::AddToWidget(edit, dialog);
	Sexy::AddToWidget(dialog, WIDGETMANAGER);
	system("pause");
	PVZ::Memory::immediateExecute = false;
	Sexy::RemoveFromWidget(edit, dialog);
	Sexy::FreeWidget(edit);
	PVZ::Memory::WriteMemory<DWORD>(0x702004, 0);
	Sexy::RemoveFromWidget(dialog, WIDGETMANAGER);
	Sexy::FreeWidget(dialog);
	PVZ::Memory::WriteMemory<DWORD>(0x702000, 0);

	PVZ::QuitPVZ();
	return 0;
}
