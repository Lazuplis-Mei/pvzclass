#pragma once
#include "DLLEvent.h"

// 更新 GameObject 事件。
// 时序上先于 PVZ 本体的更新函数。
// 该事件不可被取消。
// 该事件需要测试。
// @param 更新的 Board。
class UpdateGameObjectsEvent : public DLLEvent
{
public:
	UpdateGameObjectsEvent();
};

UpdateGameObjectsEvent::UpdateGameObjectsEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onGameObjectsUpdate");
	hookAddress = 0x4130D0;
	RegisterType args[] = { R_EBX };
	start2(procAddress, STRING(args));
}
