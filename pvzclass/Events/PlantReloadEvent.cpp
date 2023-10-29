#include "PlantReloadEvent.h"

PlantReloadEvent::PlantReloadEvent()
{
	address = 0x45F8C4;
}

#if defined(_WIN64)
void PlantReloadEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Rsi);
	int cd = context.Rcx;
	for (int i = 0; i < listeners.size(); i++)
	{
		cd = listeners[i](plant, cd);
	}
	context.Rcx = cd;
}
#else
void PlantReloadEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Esi);
	int cd = context.Ecx;
	for (int i = 0; i < listeners.size(); i++)
	{
		cd = listeners[i](plant, cd);
	}
	context.Ecx = cd;
}
#endif