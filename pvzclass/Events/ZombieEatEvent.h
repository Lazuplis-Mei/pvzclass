#pragma once
#include "DLLEvent.h"

// ��ʬ��ʳֲ���¼�
// �����������¼��Ľ�ʬ��ֲ��
// �޷���ֵ
class ZombieEatEvent : public DLLEvent
{
public:
	ZombieEatEvent();
};

ZombieEatEvent::ZombieEatEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieEat");
	hookAddress = 0x52FB40;
	RegisterType args[] = { R_EAX, R_EDI };
	start2(procAddress, STRING(args));
}
