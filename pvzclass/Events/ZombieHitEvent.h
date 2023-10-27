#pragma once
#include "TemplateEvent.h"

// 僵尸受伤事件
// 参数：触发事件的僵尸，伤害类型，伤害数值
// 返回值：更新后的伤害值
// 多个事件之间伤害会串联修改，例如基础伤害20
// 第一个监听器翻倍至40，第二个事件监听到的伤害数值就是40
// 如不作其它修改，僵尸最后会受到40点伤害
class ZombieHitEvent : public TemplateEvent<std::function<
	int(std::shared_ptr<PVZ::Zombie>, DamageType::DamageType, int)>>
{
public:
	ZombieHitEvent();
	void handle(CONTEXT& context) override;
};

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