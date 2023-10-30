#pragma once
#include "TemplateEvent.h"

// 植物消失事件
// 参数：触发事件的植物
// 无返回值
// 植物消失原因多种多样：被铲掉、被啃食、一次性植物生效、紫卡植物升级等都会触发
class PlantRemoveEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantRemoveEvent();
	void handle(CONTEXT& context) override;
};