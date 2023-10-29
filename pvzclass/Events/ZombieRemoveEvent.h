#pragma once
#include "TemplateEvent.h"

// 僵尸被移除事件
// 参数：触发事件的僵尸
// 无返回值
// 僵尸被移除的原因多种多样，即使是关卡僵尸预览界面的僵尸被移除也会触发该事件
class ZombieRemoveEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieRemoveEvent();
	void handle(CONTEXT& context) override;
};