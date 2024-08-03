#pragma once
#include "DLLEvent.h"

// 子弹消失事件
// 参数：消失的子弹
// 返回值：1取消子弹消失，0子弹正常消失
// 子弹消失的原因多种多样：命中僵尸、射出屏幕等都会触发
// 开发时注意不要取消那些射出屏幕本该移除的子弹的消失事件
class ProjectileRemoveEvent : public DLLEvent
{
public:
	ProjectileRemoveEvent();
};

ProjectileRemoveEvent::ProjectileRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileRemove");
	hookAddress = 0x46EB20;
	rawlen = 5;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4), TEST_AL_AL, JE(2), POPAD, RET };
	start(STRING(code));
}
