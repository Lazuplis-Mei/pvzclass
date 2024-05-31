#pragma once
#include "DLLEvent.h"

// 僵尸受伤事件
// 参数：触发事件的僵尸，伤害类型，伤害数值
// 返回值：更新后的伤害值
// 多个事件之间伤害会串联修改，例如基础伤害20
// 第一个监听器翻倍至40，第二个事件监听到的伤害数值就是40
// 如不作其它修改，僵尸最后会受到40点伤害
class ZombieHitEvent : public DLLEvent
{
public:
	ZombieHitEvent();
};

ZombieHitEvent::ZombieHitEvent()
{
	int procAddress = PVZ::Memory::GetProcAddress("onZombieHit");
	hookAddress = 0x5317C0;
	rawlen = 7;
	BYTE code[] = { PUSH_PTR_ESP_ADD_V(36), PUSH_EAX, PUSH_ESI, INVOKE(procAddress), ADD_ESP(12), MOV_PTR_ESP_ADD_V_EUX(0, 36)};
	start(STRING(code));
}
