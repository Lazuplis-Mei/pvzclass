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
	EnableBackgroundRunning();

	cout << std::hex << PVZ::Memory::Variable + 0x600 << endl;
	int address = PVZ::Memory::InjectDll("testdll.dll");
	cout << address << endl;
	address = PVZ::Memory::GetProcAddress(address, "MyFunction");
	cout << address << endl;
	byte invoke[] = {INVOKE(address), RET};
	PVZ::Memory::Execute(STRING(invoke));
	system("pause");

	PVZ::QuitPVZ();
	return 0;
}
