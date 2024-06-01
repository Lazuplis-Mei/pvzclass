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
	Sexy::ButtonListener listener;
	int address, buttonAddress;
	int fromAddress = PVZ::Memory::AllocMemory();
	int toAddress = fromAddress + 0x100;
	int isnewAddress = fromAddress + 0x200;
	int sharedImageRef = fromAddress + 0x210;
	int imageAddress = fromAddress + 0x220;
	BYTE filename[] = "images/test.png";
	PVZ::Memory::WriteArray<BYTE>(fromAddress, STRING(filename));
	Draw::ToString(fromAddress, toAddress);
	Draw::GetSharedImage(isnewAddress, toAddress, toAddress, sharedImageRef);
	imageAddress = Draw::SharedImageRefToImage(sharedImageRef);
	buttonAddress = Sexy::MakeImageButton(imageAddress, imageAddress, imageAddress,
		PVZ::Memory::ReadMemory<DWORD>(0x6A72D8), toAddress, &listener, 0, address);
	Sexy::AddToManager(buttonAddress);
	Sexy::ResizeButton(buttonAddress, 350, 250, 100, 100);
	system("pause");
	Sexy::RemoveFromManager(buttonAddress);
	Sexy::FreeButton(buttonAddress, address);
	Draw::FreeImage(sharedImageRef);
	PVZ::Memory::FreeMemory(fromAddress);

	PVZ::QuitPVZ();
	return 0;
}
