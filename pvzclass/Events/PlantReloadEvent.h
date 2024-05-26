#pragma once
#include "DLLEvent.h"

// 植物重新装填事件
// 参数：触发事件的植物，生效倒计时
// 返回值：修改后的倒计时
// 监听器之间串联修改
// 注：植物每隔一段时间就重新装填，此时如果发现僵尸则射击
// 生效倒计时默认为生效间隔减去一个[0,14]的随机数
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
