#include "VaseOpenEvent.h"

using Mem = PVZ::Memory;

VaseOpenEvent::VaseOpenEvent()
{
	address = 0x429AC0;
}

void VaseOpenEvent::handle(CONTEXT& context)
{
	bool cancelled = false;
#ifdef _WIN64
	auto vase = MKS<PVZ::Vase>(Mem::ReadMemory<DWORD>(context.Rsp + 8));
#else
	auto vase = MKS<PVZ::Vase>(Mem::ReadMemory<DWORD>(context.Esp + 8));
#endif

	for (int i = 0; i < listeners.size(); i++)
	{
		vase = listeners[i](vase, cancelled);
		if (cancelled)
			break;
	}
	if (cancelled)
	{
#ifdef _WIN64
		context.Rip = 0x429DA1;
#else
		context.Eip = 0x429DA1;
#endif

	}
	else
	{
#ifdef _WIN64
		Mem::WriteMemory<DWORD>(context.Rsp + 8, vase->GetBaseAddress());
#else
		Mem::WriteMemory<DWORD>(context.Esp + 8, vase->GetBaseAddress());
#endif
		
	}
}