#pragma once
#include "DLLEvent.h"

// ��ʬ�����������¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
class ZombieButterEvent : public DLLEvent
{
public:
	ZombieButterEvent();
};

ZombieButterEvent::ZombieButterEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieButter");
	hookAddress = 0x5326D0;
	rawlen = 10;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
