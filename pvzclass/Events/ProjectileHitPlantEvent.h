#pragma once
#include "DLLEvent.h"

// 子弹命中植物事件
// 参数：子弹与被命中的植物
// 返回值：被命中的植物地址，0为判定未命中
// 如果返回其它植物也可以做到一些有意思的事情
class ProjectileHitPlantEvent : public DLLEvent
{
public:
	ProjectileHitPlantEvent();
};

ProjectileHitPlantEvent::ProjectileHitPlantEvent()
{
	// 将返回集中到一个地方
	PVZ::Memory::WriteMemory<BYTE>(0x46CBBF, 0xEB);
	PVZ::Memory::WriteMemory<BYTE>(0x46CBC0, 0x63);
	PVZ::Memory::WriteMemory<BYTE>(0x46CC18, 0xEB);
	PVZ::Memory::WriteMemory<BYTE>(0x46CC19, 0x0A);
	int procAddress = PVZ::Memory::GetProcAddress("onProjectileHitPlant");
	hookAddress = 0x46CC28;
	rawlen = 6;
	BYTE code[] = { CMP_EAX_DWORD(0), JE(22), PUSH_EAX, PUSH_EBP,
		INVOKE(procAddress), ADD_ESP(8), MOV_PTR_ESP_ADD_V_EUX(0, 28) };
	start(STRING(code));
}
