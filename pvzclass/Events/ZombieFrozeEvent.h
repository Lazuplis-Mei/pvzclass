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
	rawlen = 6;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
