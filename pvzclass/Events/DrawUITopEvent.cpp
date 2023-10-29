#include "DrawUITopEvent.h"

DrawUITopEvent::DrawUITopEvent()
{
	address = 0x4172F6;
}

void DrawUITopEvent::handle(CONTEXT& context)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i]();
	}
}