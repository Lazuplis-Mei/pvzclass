#pragma once
#include "BaseEvent.h"

// 解谜关卡完成事件
// 参数：触发事件时的 Miscellaneous，X坐标，Y坐标
// 返回值：更新后的Y坐标
// 多个事件之间Y坐标会串联修改
class PuzzlePhaseCompleteEvent : public BaseEvent<std::function<
	int(SPT<PVZ::Miscellaneous>, int, int)>>
{
public:
	PuzzlePhaseCompleteEvent();
	bool handle(EventHandler handler);
};

PuzzlePhaseCompleteEvent::PuzzlePhaseCompleteEvent()
{
	address = 0x429980;
}

bool PuzzlePhaseCompleteEvent::handle(EventHandler handler)
{
	if (handler.context.Eip != address) return false;
	auto challenge = MKS<PVZ::Miscellaneous>(PVZ::Memory::ReadMemory<DWORD>(handler.context.Ecx + 4));
	int gridX = handler.context.Eax;
	int gridY = PVZ::Memory::ReadMemory<DWORD>(handler.context.Esp + 4);
	for (int i = 0; i < listeners.size(); i++)
	{
		gridY = listeners[i](challenge, gridX, gridY);
	}
	PVZ::Memory::WriteMemory<DWORD>(handler.context.Esp + 4, gridY);
	afterHandle(handler);
	return true;
}