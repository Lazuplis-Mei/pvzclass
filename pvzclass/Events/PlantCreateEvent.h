#pragma once
#include "DLLEvent.h"

// ֲ�ﴴ���¼�
// �����������¼���ֲ��
// �޷���ֵ
class PlantCreateEvent : public DLLEvent
{
public:
	PlantCreateEvent();
};

PlantCreateEvent::PlantCreateEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPlantCreate");
	hookAddress = 0x40D190;
	rawlen = 8;
	BYTE code[] = { PUSH_EAX, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}