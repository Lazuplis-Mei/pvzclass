#include "ZombieFrozeEvent.h"

ZombieFrozeEvent::ZombieFrozeEvent()
{
	address = 0x5323C0;
}

#if defined(_WIN64)
void ZombieFrozeEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#else
void ZombieFrozeEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#endif