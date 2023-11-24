#include "ImitaterPlantEvent.h"

using Mem = PVZ::Memory;

ImitaterPlantEvent::ImitaterPlantEvent()
{
	address = 0x466B89;
}

void ImitaterPlantEvent::handle(CONTEXT& context)
{
	bool cancelled = false;
#ifdef _WIN64
	auto plant = MKS<PVZ::Plant>(context.Rsi);
#else
	auto plant = MKS<PVZ::Plant>(context.Esi);
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
		context.Rip = 0x466C94;
#else
		context.Eip = 0x466C94;
#endif

	}
	else
	{
#ifdef _WIN64
		context.Rsi = plant->GetBaseAddress();
#else
		context.Esi = plant->GetBaseAddress();
#endif

	}
}