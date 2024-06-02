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

	PlantCreateEvent();
	PlantRemoveEvent();
	DrawUITopEvent();
	Sexy::ButtonListener listener;
	Sexy::PButtonListener plistener = Sexy::MakeListener(&listener);
	Draw::PString filename = Draw::ToString("images/test.png");
	int isnewAddress = PVZ::Memory::AllocMemory(0, 4);
	Draw::PSharedImageRef imageRef = Draw::GetSharedImage(isnewAddress, filename, filename);
	Draw::PImage image = Draw::SharedImageRefToImage(imageRef);
	Sexy::PButton button = Sexy::MakeImageButton(image, image, image,
		PVZ::Memory::ReadMemory<DWORD>(0x6A72D8), filename, plistener, 0);
	Sexy::AddToManager(button);
	Sexy::ResizeButton(button, 350, 250, 100, 100);
	system("pause");
	Sexy::RemoveFromManager(button);
	Sexy::FreeButton(button);
	Draw::FreeImage(imageRef);
	PVZ::Memory::FreeMemory(isnewAddress);
	PVZ::Memory::FreeMemory(filename);
	PVZ::Memory::FreeMemory(plistener);

	PVZ::QuitPVZ();
	return 0;
}
