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

void EventHandler::failLog(int line, const char* message)
{
	std::cout << "[ERROR] line " << line << ": " << message << "\n";
	system("pause");
	exit(-1);
}

void EventHandler::getContext()
{
	context.ContextFlags = CONTEXT_ALL;
	HANDLE hThread = getThread(__LINE__);
	if (!GetThreadContext(hThread, &context))
	{
		failLog(__LINE__, "GetThreadContext failed!");
	}
	closeThread(hThread, __LINE__);
}

void EventHandler::setContext()
{
	HANDLE hThread = getThread(__LINE__);
	if (!SetThreadContext(hThread, &context))
	{
		failLog(__LINE__, "SetThreadContext failed!");
	}
	closeThread(hThread, __LINE__);
}

void EventHandler::continueDebug(int line)
{
	if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
	{
		failLog(__LINE__, "ContinueDebugEvent failed!");
	}
}

void EventHandler::waitDebugInfinity(int line)
{
	if (!WaitForDebugEvent(&debugEvent, -1))
	{
		failLog(__LINE__, "WaitForDebugEvent failed!");
	}
}

HANDLE EventHandler::getThread(int line)
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	if (hThread == 0)
	{
		failLog(__LINE__, "hThread is 0!");
	}
	return hThread;
}

void EventHandler::closeThread(HANDLE hThread, int line)
{
	if (!CloseHandle(hThread))
	{
		failLog(__LINE__, "CloseHandle failed!");
	}
}

void EventHandler::start()
{
	if (!DebugActiveProcess(PVZ::Memory::processId))
	{
		failLog(__LINE__, "DebugActiveProcess failed!");
	}
	waitDebugInfinity(__LINE__);
	continueDebug(__LINE__);
	for (int i = 0; i < events.size(); i++)
	{
		events[i]->start();
	}
}

#if defined(_WIN64)
bool EventHandler::run(int ms)
{
	if (!WaitForDebugEvent(&debugEvent, ms))
	{
		return false;
}
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		continueDebug(__LINE__);
		return false;
	}
	getContext();
	context.Rip--;
	for (int i = 0; i < events.size(); i++)
	{
		if (context.Rip == events[i]->address)
		{
			events[i]->handle(context);
			PVZ::Memory::WriteMemory<BYTE>(events[i]->address, events[i]->raw);
			singleStep();
			PVZ::Memory::WriteMemory<BYTE>(events[i]->address, 0xCC);
		}
	}
	resume();
	return true;
}
#else
bool EventHandler::run(int ms)
{
	if (!WaitForDebugEvent(&debugEvent, ms))
	{
		return false;
	}
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		continueDebug(__LINE__);
		return false;
	}
	getContext();
	context.Eip--;
	for (int i = 0; i < events.size(); i++)
	{
		if (context.Eip == events[i]->address)
		{
			events[i]->handle(context);
			PVZ::Memory::WriteMemory<BYTE>(events[i]->address, events[i]->raw);
			singleStep();
			PVZ::Memory::WriteMemory<BYTE>(events[i]->address, 0xCC);
		}
	}
	resume();
	return true;
}
#endif

void EventHandler::singleStep()
{
	context.EFlags |= 0x100;
	setContext();
	continueDebug(__LINE__);
	waitDebugInfinity(__LINE__);
}

void EventHandler::resume()
{
	continueDebug(__LINE__);
}

void EventHandler::stop()
{
	for (int i = 0; i < events.size(); i++)
	{
		events[i]->end();
	}
	if (!DebugActiveProcessStop(PVZ::Memory::processId))
	{
		failLog(__LINE__, "DebugActiveProcessStop failed!");
	}
}

void EventHandler::addEvent(std::shared_ptr<BaseEvent> ptr)
{
	events.push_back(ptr);
}