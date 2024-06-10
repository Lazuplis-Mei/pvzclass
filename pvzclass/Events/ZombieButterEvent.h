#pragma once
#include "DLLEvent.h"

// 僵尸被黄油命中事件
// 参数：触发事件的僵尸
// 无返回值
class ZombieButterEvent : public DLLEvent
{
public:
	ZombieButterEvent();
};

ZombieButterEvent::ZombieButterEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieButter");
	hookAddress = 0x5326D0;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
