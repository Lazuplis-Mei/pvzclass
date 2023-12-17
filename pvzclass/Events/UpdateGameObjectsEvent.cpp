#include "UpdateGameObjectsEvent.h"

using Mem = PVZ::Memory;

UpdateGameObjectsEvent::UpdateGameObjectsEvent()
{
	address = 0x4130D0;
}

void UpdateGameObjectsEvent::handle(CONTEXT& context)
{
#ifdef _WIN64
	auto board = MKS<PVZ::Board>(context.Rbx);
#else
	auto board = MKS<PVZ::Board>(context.Ebx);
#endif

	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](board);
	}
}