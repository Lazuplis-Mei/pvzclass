#pragma once
#include "TemplateEvent.h"

// 子弹创建事件
// 参数：被创建的子弹
// 无返回值
class ProjectileCreateEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Projectile>)>>
{
public:
	ProjectileCreateEvent();
	void handle(CONTEXT& context) override;
};

ProjectileCreateEvent::ProjectileCreateEvent()
{
	address = 0x40D652;
}

#if defined(_WIN64)
void ProjectileCreateEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Rax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#else
void ProjectileCreateEvent::handle(CONTEXT& context)
{
	auto projectile = std::make_shared<PVZ::Projectile>(context.Eax);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](projectile);
	}
}
#endif