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