#pragma once
#include "TemplateEvent.h"

// 僵尸被魅惑事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieHypnotizeEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieHypnotizeEvent();
	bool handle(EventHandler handler);
};

ZombieHypnotizeEvent::ZombieHypnotizeEvent()
{
	address = 0x52FA60;
}

bool ZombieHypnotizeEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(handler.context.Esi);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
	afterHandle(handler);
	return true;
}