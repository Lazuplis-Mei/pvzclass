#pragma once
#include "TemplateEvent.h"

// 僵尸灰烬事件
// 参数：触发事件的僵尸
// 无返回值
// 僵尸受到灰烬伤害就会触发
class ZombieBlastEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>)>>
{
public:
	ZombieBlastEvent();
	void handle(CONTEXT& context) override;
};