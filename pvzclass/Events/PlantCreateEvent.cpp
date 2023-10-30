#include "PlantCreateEvent.h"

PlantCreateEvent::PlantCreateEvent()
{
	address = 0x40D190;
}

#if defined(_WIN64)
void PlantCreateEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#else
void PlantCreateEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#endif