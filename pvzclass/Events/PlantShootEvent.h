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
	rawlen = 6;
	BYTE code[] = { PUSH_EBP, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
