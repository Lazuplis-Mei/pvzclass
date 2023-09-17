#pragma once
#include "TemplateEvent.h"

// 僵尸被黄油命中事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieButterEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieButterEvent();
	bool handle(EventHandler handler);
};

ZombieButterEvent::ZombieButterEvent()
{
	address = 0x5326D0;
}

bool ZombieButterEvent::handle(EventHandler handler)
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