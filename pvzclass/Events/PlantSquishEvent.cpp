#include "PlantSquishEvent.h"

using Mem = PVZ::Memory;

PlantSquishEvent::PlantSquishEvent()
{
	address = 0x462B80;
}

void PlantSquishEvent::handle(CONTEXT& context)
{
	bool cancelled = false;
#ifdef _WIN64
	auto plant = MKS<PVZ::Plant>(Mem::ReadMemory<DWORD>(context.Rsp + 4));
#else
	auto plant = MKS<PVZ::Plant>(Mem::ReadMemory<DWORD>(context.Esp + 4));
#endif

	for (int i = 0; i < listeners.size(); i++)
	{
		plant = listeners[i](plant, cancelled);
		if (cancelled)
			break;
	}
	if (cancelled)
	{
#ifdef _WIN64
		context.Rip = 0x462CD0;
#else
		context.Eip = 0x462CD0;
#endif

	}
	else
	{
#ifdef _WIN64
		Mem::WriteMemory<DWORD>(context.Rsp + 4, plant->GetBaseAddress());
#else
		Mem::WriteMemory<DWORD>(context.Esp + 4, plant->GetBaseAddress());
#endif
		
	}
}