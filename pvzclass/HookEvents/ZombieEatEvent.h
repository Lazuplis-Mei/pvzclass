#pragma once
#include "BaseEvent.h"

// 参数：啃食的僵尸指针，被啃食的植物指针
// 无返回值
class ZombieEatEvent : public BaseEvent<std::function<
	void(std::shared_ptr<PVZ::Zombie>, std::shared_ptr<PVZ::Plant>)>>
{
public:
	void start();
	void run();
	void end();
};
