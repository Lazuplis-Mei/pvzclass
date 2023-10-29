#include "ProjectileCreateEvent.h"

ProjectileCreateEvent::ProjectileCreateEvent()
{
	address = 0x40D652;
}

#if defined(_WIN64)
void ProjectileCreateEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#else
void ProjectileCreateEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#endif