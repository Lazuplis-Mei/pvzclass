#include "ZombieDecelerateEvent.h"

ZombieDecelerateEvent::ZombieDecelerateEvent()
{
	address = 0x530950;
}

#if defined(_WIN64)
void ZombieDecelerateEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#else
void ZombieDecelerateEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
}
#endif