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

	printf("%#08X", procAddress);

	RegisterType args[] = { R_EAX };
	start2(procAddress, STRING(args));
}