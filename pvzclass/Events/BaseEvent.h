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