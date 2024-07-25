#pragma once
#include "DLLEvent.h"

// 植物消失事件
// 参数：触发事件的植物
// 无返回值
// 植物消失原因多种多样：被铲掉、被啃食、一次性植物生效、紫卡植物升级等都会触发
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
