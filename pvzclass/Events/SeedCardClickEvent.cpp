#include "SeedCardClickEvent.h"

SeedCardClickEvent::SeedCardClickEvent()
{
	address = 0x412236;
}

#if defined(_WIN64)
void SeedCardClickEvent::handle(CONTEXT& context)
{
	auto seedcard = std::make_shared<PVZ::CardSlot::SeedCard>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](seedcard);
	}
}
#else
void SeedCardClickEvent::handle(CONTEXT& context)
{
	auto seedcard = std::make_shared<PVZ::CardSlot::SeedCard>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](seedcard);
	}
}
#endif