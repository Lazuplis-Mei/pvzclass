#include "ProjectileRemoveEvent.h"

ProjectileRemoveEvent::ProjectileRemoveEvent()
{
	address = 0x46EB20;
}

#if defined(_WIN64)
void ProjectileRemoveEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#else
void ProjectileRemoveEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#endif