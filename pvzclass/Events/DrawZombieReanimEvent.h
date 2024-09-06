#pragma once
#include "DLLEvent.h"
#define MOV_VAR(u, v) 0x8B, 0x43, u, 0x89, 0x44, 0x24, (0x20 + v)

// 绘制僵尸动画事件
// 参数：绘制的僵尸和对应的动画
// 返回值：如果僵尸手持护盾并且修改了颜色，请返回1，否则返回0以减少性能消耗
// 事件触发在颜色计算之后和绘制发生之前
class DrawZombieReanimEvent : public DLLEvent
{
public:
	DrawZombieReanimEvent();
};

DrawZombieReanimEvent::DrawZombieReanimEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onDrawZombieReanim");
	hookAddress = 0x52D429;
	rawlen = 6;
	BYTE code[] = { PUSH_EBX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(8),
		CMP_EAX_DWORD(0), JE(67), // 25
		0x8B, 0x5C, 0x24, 0x10, // mov ebx, [esp+10]
		MOV_VAR(0x48, 0x30),
		MOV_VAR(0x4C, 0x34),
		MOV_VAR(0x50, 0x38),
		MOV_VAR(0x54, 0x3C),
		MOV_VAR(0x6C, 0x20),
		MOV_VAR(0x70, 0x24),
		MOV_VAR(0x74, 0x28),
		MOV_VAR(0x78, 0x2C),
		0x8A, 0x43, 0x7C, // mov al, [ebx+7C]
		0x88, 0x44, 0x24, 0x2F // mov [esp+2F], al
	};
	start(STRING(code));
}
