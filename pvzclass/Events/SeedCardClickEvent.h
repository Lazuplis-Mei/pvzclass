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
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
