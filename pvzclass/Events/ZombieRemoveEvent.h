#pragma once
#include "DLLEvent.h"

// 僵尸被移除事件
// 参数：触发事件的僵尸
// 无返回值
// 僵尸被移除的原因多种多样，即使是关卡僵尸预览界面的僵尸被移除也会触发该事件
class ZombieRemoveEvent : public DLLEvent
{
public:
	ZombieRemoveEvent();
};

ZombieRemoveEvent::ZombieRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieRemove");
	hookAddress = 0x530510;
	RegisterType args[] = { R_ECX };
	start2(procAddress, STRING(args));
}
