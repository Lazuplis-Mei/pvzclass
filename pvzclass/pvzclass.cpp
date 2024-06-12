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
	PVZ::Memory::immediateExecute = false;

	system("pause");
	DialogButtonDepressEvent();
	DialogDrawEvent();
	system("pause");
	Sexy::CheckboxListener listener;
	Sexy::PCheckboxListener plistener = Sexy::MakeCheckboxListener(&listener);
	Sexy::PCheckbox checkbox = Sexy::MakeCheckbox(0, plistener, 0);
	Sexy::ResizeWidget(checkbox, 380, 280, 40, 35);
	Sexy::AddToWidget(checkbox, WIDGETMANAGER);
	system("pause");
	bool checked = Sexy::IsCheckboxChecked(checkbox);
	cout << checked << endl;
	Sexy::setCheckboxChecked(checkbox, !checked, true);
	system("pause");
	Sexy::RemoveFromWidget(checkbox, WIDGETMANAGER);
	Sexy::FreeWidget(checkbox);

	PVZ::QuitPVZ();
	return 0;
}
