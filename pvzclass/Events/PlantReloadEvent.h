#pragma once
#include "DLLEvent.h"

// ֲ������װ���¼�
// �����������¼���ֲ���Ч����ʱ
// ����ֵ���޸ĺ�ĵ���ʱ
// ������֮�䴮���޸�
// ע��ֲ��ÿ��һ��ʱ�������װ���ʱ������ֽ�ʬ�����
// ��Ч����ʱĬ��Ϊ��Ч�����ȥһ��[0,14]�������
class PlantReloadEvent : public DLLEvent
{
public:
	PlantReloadEvent();
};

PlantReloadEvent::PlantReloadEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onPlantReload");
	hookAddress = 0x45F8C4;
	rawlen = 6;
	BYTE code[] = { PUSH_ECX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 24) };
	start(STRING(code));
}
