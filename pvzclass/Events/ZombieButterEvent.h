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
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
