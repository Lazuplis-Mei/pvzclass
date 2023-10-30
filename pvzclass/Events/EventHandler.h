#pragma once
#include "../PVZ.h"
#include "TemplateEvent.h"
#include <vector>
#include <iostream>

class EventHandler
{
private:
	DEBUG_EVENT debugEvent;
	CONTEXT context;
	void failLog(int line, const char* message);
	void getContext();
	void setContext();
	void singleStep();
	void continueDebug(int line);
	void waitDebugInfinity(int line);
	HANDLE getThread(int line);
	void closeThread(HANDLE hThread, int line);
	void resume();

protected:
	std::vector<std::shared_ptr<BaseEvent>> events;

public:
	// 开始调试PVZ进程，会有一小段卡顿
	void start();

	// 等待至多ms的时间，返回是否出现系统中断
	// ms至少为1，可以用-1代表无限等待
	// 如果返回值为true，需要调用handle()和resume()
	bool run(int ms);

	// 停止调试PVZ进程
	void stop();

	// 增加一个事件，指针的类型应该是事件的实际类型而非BaseEvent
	void addEvent(std::shared_ptr<BaseEvent> ptr);
};