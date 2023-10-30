#pragma once
#include "TemplateEvent.h"

// 子弹命中僵尸事件
// 参数：子弹与被命中的僵尸
// 无返回值
class ProjectileHitZombieEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Projectile>, std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ProjectileHitZombieEvent();
	void handle(CONTEXT& context) override;
};