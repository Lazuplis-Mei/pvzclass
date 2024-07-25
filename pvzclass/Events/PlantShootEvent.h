#pragma once
#include "DLLEvent.h"

// 植物射击事件
// 参数：触发事件的植物
// 无返回值
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
