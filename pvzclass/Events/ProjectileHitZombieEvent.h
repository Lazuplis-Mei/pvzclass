#pragma once
#include "DLLEvent.h"

// 子弹命中僵尸事件
// 参数：子弹与被命中的僵尸
// 无返回值
class ProjectileHitZombieEvent : public DLLEvent
{
public:
	ProjectileHitZombieEvent();
};

ProjectileHitZombieEvent::ProjectileHitZombieEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileHitZombie");
	hookAddress = 0x46CE74;
	rawlen = 6;
	BYTE code[] = { CMP_EAX_DWORD(0), JE(18), PUSH_EAX, PUSH_EBP, INVOKE(procAddress), ADD_ESP(8) };
	start(STRING(code));
}
