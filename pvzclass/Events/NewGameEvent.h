#pragma once
#include "DLLEvent.h"

// ����Ϸ��ʼʱ��PVZGameState��ΪPreparing֮��
// ��ʱ��Ϸ�Ѿ�����˹ؿ��ĸ��ּ��غ�׼��
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
