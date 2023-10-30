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
	void handle(CONTEXT& context) override;
};