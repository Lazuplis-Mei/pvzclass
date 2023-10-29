#pragma once
#include "TemplateEvent.h"

// 植物创建事件
// 参数：触发事件的植物
// 无返回值
class PlantCreateEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantCreateEvent();
	void handle(CONTEXT& context) override;
};