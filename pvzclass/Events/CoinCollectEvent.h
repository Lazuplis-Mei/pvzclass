#pragma once
#include "DLLEvent.h"

// Coin收集事件
// 参数：触发事件的Coin
// 无返回值
class CoinCollectEvent : public DLLEvent
{
public:
	CoinCollectEvent();
};

CoinCollectEvent::CoinCollectEvent()
{
	procname = "onCoinCollect";
	rawlen = 6;
	newlen = 30;
	hookAddress = 0x432060;
	prepare();
	BYTE code1[] = { JMPFAR(newAddress - (0x432060 + 5)), NOP };
	hookCode = code1;
	BYTE code2[] = { PUSHAD, 0x51, INVOKE(procAddress), ADD_ESP(4), POPAD, 0x55, 0x8B, 0xEC, 0x83, 0xE4, 0xF8, JMPFAR(0x432066 - (newAddress + 30)) };
	newCode = code2;
	start();
}