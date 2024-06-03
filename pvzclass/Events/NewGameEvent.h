#pragma once
#include "DLLEvent.h"

// 新游戏开始时，PVZGameState变为Preparing之后
// 此时游戏已经完成了关卡的各种加载和准备
class NewGameEvent : public DLLEvent
{
public:
	NewGameEvent();
};

NewGameEvent::NewGameEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onNewGame");
	hookAddress = 0x44F8D8;
	rawlen = 5;
	BYTE code[] = { INVOKE(procAddress) };
	start(STRING(code));
}
