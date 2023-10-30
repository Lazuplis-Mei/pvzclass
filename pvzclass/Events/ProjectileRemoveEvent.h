#pragma once
#include "TemplateEvent.h"

// 子弹消失事件
// 参数：消失的子弹
// 无返回值
// 子弹消失的原因多种多样：命中僵尸、射出屏幕等都会触发
class ProjectileRemoveEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Projectile>)>>
{
public:
	ProjectileRemoveEvent();
	void handle(CONTEXT& context) override;
};