#pragma once
#include "../PVZ.h"
#include <iostream>
#include <vector>

class BaseEvent
{
public:
	DWORD address;
	BYTE raw;
	// 开始监听这个事件，不需要用户调用
	void start();
	// 处理事件，不需要用户调用
	virtual void handle(CONTEXT& context);
	// 结束事件，不需要用户调用
	void end();
	BaseEvent();
};

BaseEvent::BaseEvent()
{
	address = 0;
	raw = 0;
}

void BaseEvent::start()
{
	raw = PVZ::Memory::ReadMemory<BYTE>(address);
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
}

void BaseEvent::end()
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
}

void BaseEvent::handle(CONTEXT& context)
{
	std::cout << "调用了BaseEvent的handle()，这不应该发生！\n";
}