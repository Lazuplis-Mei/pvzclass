#pragma once
#include "DLLEvent.h"

// ֲ����ʧ�¼�
// �����������¼���ֲ��
// �޷���ֵ
// ֲ����ʧԭ����ֶ�����������������ʳ��һ����ֲ����Ч���Ͽ�ֲ�������ȶ��ᴥ��
class PlantRemoveEvent : public DLLEvent
{
public:
	PlantRemoveEvent();
};

PlantRemoveEvent::PlantRemoveEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPlantRemove");
	printf("%#08X", procAddress);
	hookAddress = 0x4679B9;
	RegisterType args[] = { R_EBP };
	start2(procAddress, STRING(args));
}
