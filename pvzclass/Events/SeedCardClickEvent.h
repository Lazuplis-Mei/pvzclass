#pragma once
#include "DLLEvent.h"

// �����еĿ�Ƭ������¼�
// ������SeedCard
// �޷���ֵ
class SeedCardClickEvent : public DLLEvent
{
public:
	SeedCardClickEvent();
};

SeedCardClickEvent::SeedCardClickEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onSeedCardClick");
	hookAddress = 0x488590;
	rawlen = 8;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
