#pragma once
#include "DLLEvent.h"

// ��ʬ�������¼�
// �����������¼��Ľ�ʬ
// �޷���ֵ
class ZombieDecelerateEvent : public DLLEvent
{
public:
	ZombieDecelerateEvent();
};

ZombieDecelerateEvent::ZombieDecelerateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieDecelerate");
	hookAddress = 0x530950;
	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}
