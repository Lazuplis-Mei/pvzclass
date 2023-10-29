#pragma once
#include "TemplateEvent.h"

// 植物射击事件
// 参数：触发事件的植物
// 无返回值
class PlantShootEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>)>>
{
public:
	PlantShootEvent();
	void handle(CONTEXT& context) override;
};