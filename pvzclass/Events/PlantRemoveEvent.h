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
	hookAddress = 0x4679B9;
	rawlen = 7;
	BYTE code[] = { PUSH_EBP, INVOKE(procAddress), ADD_ESP(4) };
	start(STRING(code));
}
