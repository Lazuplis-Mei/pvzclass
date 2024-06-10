#pragma once
#include "DLLEvent.h"

// 僵尸啃食植物事件
// 参数：触发事件的僵尸和植物
// 无返回值
class ZombieEatEvent : public DLLEvent
{
public:
	ZombieEatEvent();
};

ZombieEatEvent::ZombieEatEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieEat");
	hookAddress = 0x52FB40;
	RegisterType args[] = { R_EAX, R_EDI };
	start2(procAddress, STRING(args));
}
