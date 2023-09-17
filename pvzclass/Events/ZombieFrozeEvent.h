#pragma once
#include "TemplateEvent.h"

// 僵尸被冻结事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieFrozeEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieFrozeEvent();
	bool handle(EventHandler handler);
};

ZombieFrozeEvent::ZombieFrozeEvent()
{
	address = 0x5323C0;
}

bool ZombieFrozeEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto zombie = std::make_shared<PVZ::Zombie>(handler.context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](zombie);
	}
	afterHandle(handler);
	return true;
}