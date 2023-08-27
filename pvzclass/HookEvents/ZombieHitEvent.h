#pragma once
#include "BaseEvent.h"

extern BYTE hook_700010[62];
extern BYTE hook_5317C0[7];
extern BYTE hook_5317C0_raw[7];

// 参数：僵尸，伤害类型，伤害数值
// 返回：新的伤害数值
// 注：各个 listener 的数值改动为串联
class ZombieHitEvent : public BaseEvent<std::function<
	int(std::shared_ptr<PVZ::Zombie>, DamageType::DamageType, int)>>
{
public:
	void start();
	void run();
	void end();
};
