#pragma once
#include "DLLEvent.h"

// 子弹创建事件
// 参数：被创建的子弹
// 无返回值
class ProjectileCreateEvent : public DLLEvent
{
public:
	ProjectileCreateEvent();
};

ProjectileCreateEvent::ProjectileCreateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileCreate");
	hookAddress = 0x40D652;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
