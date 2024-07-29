#pragma once
#include "DLLEvent.h"

// 游戏程序的更新事件
// 该事件无论是否在关卡内都会持续触发
class UpdateAppEvent : public DLLEvent
{
public:
	UpdateAppEvent();
};

UpdateAppEvent::UpdateAppEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onAppUpdate");
	hookAddress = 0x453A50;
	rawlen = 7;
	BYTE code[] = { PUSH_ECX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
