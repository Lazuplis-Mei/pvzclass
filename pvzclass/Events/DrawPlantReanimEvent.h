#pragma once
#include "DLLEvent.h"

// ����ֲ�ﶯ���¼�
// ���������Ƶ�ֲ��Ͷ�Ӧ�Ķ���
// �¼���������ɫ����֮��ͻ��Ʒ���֮ǰ
class DrawPlantReanimEvent : public DLLEvent
{
public:
	DrawPlantReanimEvent();
};

DrawPlantReanimEvent::DrawPlantReanimEvent()
{
	PVZ::Memory::WriteMemory<BYTE>(0x4638C4, 0xEB);
	PVZ::Memory::WriteMemory<BYTE>(0x4638C5, 0x15);
	PVZ::Memory::WriteMemory<BYTE>(0x4638C6, NOP);
	PVZ::Memory::WriteMemory<BYTE>(0x4638C7, NOP);
	PVZ::Memory::WriteMemory<BYTE>(0x4638C8, NOP);
	int procAddress = PVZ::Memory::GetProcAddress("onDrawPlantReanim");
	hookAddress = 0x4638DB;
	rawlen = 5;
	BYTE code[] = { PUSH_EBX, PUSH_PTR_ESP_ADD_V(0x2C), INVOKE(procAddress), ADD_ESP(8),
		POPAD, INVOKE(0x473AE0), JMP(6)
	};
	start(STRING(code));
}
