#pragma once
#include "BaseEvent.h"

// 参数：植物指针，子弹指针
// 无返回值
// 注：杨桃的子弹指针不准
class PlantShootEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Plant>, std::shared_ptr<PVZ::Projectile>)>>
{
public:
	void start();
	void run();
	void end();
};

