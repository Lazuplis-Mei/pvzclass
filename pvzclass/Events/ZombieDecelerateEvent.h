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
	rawlen = 5;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
