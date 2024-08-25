#pragma once
#include "DLLEvent.h"

// 绘制植物动画事件
// 参数：绘制的植物和对应的动画
// 事件触发在颜色计算之后和绘制发生之前
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
