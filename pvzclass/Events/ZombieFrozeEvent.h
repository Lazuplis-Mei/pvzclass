#pragma once
#include "DLLEvent.h"

// ��ʬ�������¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
class ZombieFrozeEvent : public DLLEvent
{
public:
	ZombieFrozeEvent();
};

ZombieFrozeEvent::ZombieFrozeEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieFroze");
	hookAddress = 0x5323C0;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
