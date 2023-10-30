#include "BaseEvent.h"

BaseEvent::BaseEvent()
{
	address = 0;
	raw = 0;
}

void BaseEvent::start()
{
	raw = PVZ::Memory::ReadMemory<BYTE>(address);
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
}

void BaseEvent::end()
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
}

void BaseEvent::handle(CONTEXT& context)
{
	std::cout << "调用了BaseEvent的handle()，这不应该发生！\n";
}