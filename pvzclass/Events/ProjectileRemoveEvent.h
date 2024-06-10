#pragma once
#include "DLLEvent.h"

// 子弹消失事件
// 参数：消失的子弹
// 无返回值
// 子弹消失的原因多种多样：命中僵尸、射出屏幕等都会触发
class ProjectileRemoveEvent : public DLLEvent
{
public:
	ProjectileRemoveEvent();
};

ProjectileRemoveEvent::ProjectileRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileRemove");
	hookAddress = 0x46EB20;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
