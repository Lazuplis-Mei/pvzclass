#pragma once
#include "DLLEvent.h"

// 僵尸被减速事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieDecelerateEvent : public DLLEvent
{
public:
	ZombieDecelerateEvent();
};

ZombieDecelerateEvent::ZombieDecelerateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieDecelerate");
	hookAddress = 0x530950;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
