#include "PeaOnFireEvent.h"

PeaOnFireEvent::PeaOnFireEvent()
{
	address = 0x46ECB0;
}

#if defined(_WIN64)
void PeaOnFireEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Rcx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#else
void PeaOnFireEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#endif