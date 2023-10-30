#include "ZombieBlastEvent.h"

ZombieBlastEvent::ZombieBlastEvent()
{
	address = 0x532B70;
}

#if defined(_WIN64)
void ZombieBlastEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rcx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#else
void ZombieBlastEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#endif