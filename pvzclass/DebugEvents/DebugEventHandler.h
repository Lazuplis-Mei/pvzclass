#pragma once
#include "../PVZ.h"
#include "BaseEvent.h"
#include <vector>

class DebugEventHandler
{
private:
	void getContext();
	void setContext();

public:
	DEBUG_EVENT debugEvent;
	CONTEXT context;

	// 开始调试PVZ进程，会有一小段卡顿
	void start();

	// 等待至多ms的时间，返回是否出现系统中断
	// ms至少为1，可以用-1代表无限等待
	// 如果返回值为true，需要调用handle()和resume()
	bool run(int ms);

	// 令PVZ单步执行一个命令，不需要调用这个函数
	void singleStep();

	// 恢复PVZ的运行，需要在handle()后调用
	void resume();
	
	// 停止调试PVZ进程
	void stop();
};

void DebugEventHandler::getContext()
{
	context.ContextFlags = CONTEXT_ALL;
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	GetThreadContext(hThread, &context);
	CloseHandle(hThread);
}

void DebugEventHandler::setContext()
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	SetThreadContext(hThread, &context);
	CloseHandle(hThread);
}

void DebugEventHandler::start()
{
	DebugActiveProcess(PVZ::Memory::processId);
	WaitForDebugEvent(&debugEvent, -1);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
}

bool DebugEventHandler::run(int ms)
{
	WaitForDebugEvent(&debugEvent, ms);
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
		return false;
	}
	getContext();
	context.Eip--;
	return true;
}

void DebugEventHandler::singleStep()
{
	context.EFlags |= 0x100;
	setContext();
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	WaitForDebugEvent(&debugEvent, -1);
}

void DebugEventHandler::resume()
{
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
}

void DebugEventHandler::stop()
{
	DebugActiveProcessStop(PVZ::Memory::processId);
}