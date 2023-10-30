#include "ZombieEatEvent.h"

ZombieEatEvent::ZombieEatEvent()
{
	address = 0x52F689;
}

#if defined(_WIN64)
void ZombieEatEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rdi);
	auto plant = std::make_shared<PVZ::Plant>(context.Rcx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie, plant);
	}
}
#else
void ZombieEatEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Edi);
	auto plant = std::make_shared<PVZ::Plant>(context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie, plant);
	}
}
#endif