#pragma once
#include "DLLEvent.h"

// 子弹命中僵尸事件
// 参数：子弹与被命中的僵尸
// 返回值：被命中的僵尸地址，0为判定未命中
// 如果返回其它僵尸也可以做到一些有意思的事情
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
	BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
		INVOKE(procAddress), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
	start(STRING(code));
}
