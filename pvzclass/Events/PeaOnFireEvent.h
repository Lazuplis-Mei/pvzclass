#pragma once
#include "TemplateEvent.h"

// 豌豆穿过火炬树桩的着火事件
// 参数：即将变为火球的豌豆
// 无返回值
class PeaOnFireEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Projectile>)>>
{
public:
	PeaOnFireEvent();
	bool handle(EventHandler handler);
};

PeaOnFireEvent::PeaOnFireEvent()
{
	address = 0x46ECB0;
}

bool PeaOnFireEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto projectile = std::make_shared<PVZ::Projectile>(handler.context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
	afterHandle(handler);
	return true;
}
