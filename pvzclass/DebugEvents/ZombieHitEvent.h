#pragma once
#include "BaseEvent.h"

// 僵尸受伤事件
// 参数：触发事件的僵尸，伤害类型，伤害数值
// 返回值：更新后的伤害值
// 多个事件之间伤害会串联修改，例如基础伤害20
// 第一个监听器翻倍至40，第二个事件监听到的伤害数值就是40
// 如不作其它修改，僵尸最后会受到40点伤害
class ZombieHitEvent : public BaseEvent<std::function<
	int(std::shared_ptr<PVZ::Zombie>, DamageType::DamageType, int)>>
{
public:
	ZombieHitEvent();
	bool handle(DebugEventHandler handler);
};

ZombieHitEvent::ZombieHitEvent()
{
	address = 0x5317C0;
}

bool ZombieHitEvent::handle(DebugEventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(handler.context.Esi);
	DamageType::DamageType type = (DamageType::DamageType)(handler.context.Eax);
	int amount = PVZ::Memory::ReadMemory<DWORD>(handler.context.Esp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		amount = listeners[i](zombie, type, amount);
	}
	PVZ::Memory::WriteMemory<DWORD>(handler.context.Esp + 4, amount);
	afterHandle(handler);
	return true;
}