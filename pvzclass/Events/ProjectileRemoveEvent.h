#pragma once
#include "BaseEvent.h"

// 子弹消失事件
// 参数：消失的子弹
// 无返回值
// 子弹消失的原因多种多样：命中僵尸、射出屏幕等都会触发
class ProjectileRemoveEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Projectile>)>>
{
public:
	ProjectileRemoveEvent();
	bool handle(EventHandler handler);
};

ProjectileRemoveEvent::ProjectileRemoveEvent()
{
	address = 0x46EB20;
}

bool ProjectileRemoveEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto projectile = std::make_shared<PVZ::Projectile>(handler.context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
	afterHandle(handler);
	return true;
}
