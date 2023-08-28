#pragma once
#include "BaseEvent.h"

class ZombieHitEvent : public BaseEvent<std::function<
	int(std::shared_ptr<PVZ::Zombie>, DamageType::DamageType, int)>>
{
public:
	ZombieHitEvent();
	bool handle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread);
};

ZombieHitEvent::ZombieHitEvent()
{
	address = 0x5317C0;
}

bool ZombieHitEvent::handle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread)
{
	if (context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(context.Esi);
	DamageType::DamageType type = (DamageType::DamageType)(context.Eax);
	int amount = PVZ::Memory::ReadMemory<DWORD>(context.Esp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		amount = listeners[i](zombie, type, amount);
	}
	PVZ::Memory::WriteMemory<DWORD>(context.Esp + 4, amount);
	afterHandle(debugEvent, context, hThread);
	return true;
}