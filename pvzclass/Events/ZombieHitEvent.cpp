#include "ZombieHitEvent.h"

ZombieHitEvent::ZombieHitEvent()
{
	address = 0x5317C0;
}

#if defined(_WIN64)
void ZombieHitEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Rsi);
	DamageType::DamageType type = (DamageType::DamageType)(context.Rax);
	int amount = PVZ::Memory::ReadMemory<DWORD>(context.Rsp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		amount = listeners[i](zombie, type, amount);
	}
	PVZ::Memory::WriteMemory<DWORD>(context.Rsp + 4, amount);
}
#else
void ZombieHitEvent::handle(CONTEXT& context)
{
	auto zombie = std::make_shared<PVZ::Zombie>(context.Esi);
	DamageType::DamageType type = (DamageType::DamageType)(context.Eax);
	int amount = PVZ::Memory::ReadMemory<DWORD>(context.Esp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		amount = listeners[i](zombie, type, amount);
	}
	PVZ::Memory::WriteMemory<DWORD>(context.Esp + 4, amount);
}
#endif