#include "PlantShootEvent.h"

PlantShootEvent::PlantShootEvent()
{
	address = 0x466E0D;
}

#if defined(_WIN64)
void PlantShootEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Rbp);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#else
void PlantShootEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Ebp);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](plant);
	}
}
#endif