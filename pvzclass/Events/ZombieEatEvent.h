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
	rawlen = 7;
	BYTE code[] = { PUSH_ECX, PUSH_EDI, INVOKE(procAddress), ADD_ESP(8) };
	start(STRING(code));
}
