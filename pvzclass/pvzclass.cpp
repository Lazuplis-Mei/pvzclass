#include "pvzclass.h"
#include "Events/EventHandler.h"
#include "Events/VaseOpenEvent.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;

SPT<PVZ::Vase> listenerC(SPT<PVZ::Vase> vase, bool& cancelled)
{
	if (vase->Skin == VaseSkin::VaseSkinLeaf)
	{
		vase->Skin = VaseSkin::VaseSkinZombie;
		cancelled = true;
	}
	return(vase);
}

SPT<PVZ::Vase> listenerM(SPT<PVZ::Vase> vase, bool& cancelled)
{
	std::vector<SPT<PVZ::Griditem>> vases = PVZ::GetBoard()->GetAllGriditems();
	while (vases[vases.size() - 1]->Type != GriditemType::Vase)
		vases.pop_back();
	SPT<PVZ::Griditem> cur = vases[vases.size() - 1];
	SPT<PVZ::Vase> curVase = MKS<PVZ::Vase>(cur->GetBaseAddress());
	if (vase->Skin == VaseSkin::VaseSkinZombie)
	{
		curVase->Column = 0;
		return(curVase);
	}
	else
		return(vase);
}

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ::InitPVZ(pid);
	PVZ::Memory::immediateExecute = true;
	EnableBackgroundRunning();

	cout << std::hex << PVZ::Memory::Variable + 0x600 << endl;
	int address = PVZ::Memory::InjectDll("pvzdll.dll");
	cout << address << endl;
	address = PVZ::Memory::GetProcAddress(address, "onCoinCollect");
	cout << address << endl;

	int dllHookAddress = PVZ::Memory::AllocMemory();
	cout << dllHookAddress << endl;
	byte hook_432060[] = { JMPFAR(dllHookAddress - (0x432060 + 5)), NOP };
	PVZ::Memory::WriteArray<byte>(0x432060, STRING(hook_432060));
	byte hook_event[] = { PUSHAD, 0x51, INVOKE(address), ADD_ESP(4), POPAD, 0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, JMPFAR(0x432066 - (dllHookAddress + 30)) };
	PVZ::Memory::WriteArray<byte>(dllHookAddress, STRING(hook_event));

	PVZ::QuitPVZ();
	return 0;
}
