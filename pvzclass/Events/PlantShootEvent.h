#pragma once
#include "DLLEvent.h"

// ֲ������¼�
// �����������¼���ֲ��
// �޷���ֵ
class PlantShootEvent : public DLLEvent
{
public:
	PlantShootEvent();
};

PlantShootEvent::PlantShootEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPlantShoot");
	hookAddress = 0x466E0D;
	RegisterType args[] = { R_EBP };
	start2(procAddress, STRING(args));
}
