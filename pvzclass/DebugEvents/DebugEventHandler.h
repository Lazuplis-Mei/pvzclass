#pragma once
#include "../PVZ.h"
#include "BaseEvent.h"
#include <vector>
#include <iostream>

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
	if (hThread == 0)
	{
		std::cout << "[ERROR] line " << __LINE__ << ": hThread is 0!\n";
		system("pause");
		exit(-1);
	}
	if (!GetThreadContext(hThread, &context))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": GetThreadContext failed!\n";
		system("pause");
		exit(-1);
	}
	if (!CloseHandle(hThread))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": CloseHandle failed!\n";
		system("pause");
		exit(-1);
	}
}

void DebugEventHandler::setContext()
{
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	if (hThread == 0)
	{
		std::cout << "[ERROR] line " << __LINE__ << ": hThread is 0!\n";
		system("pause");
		exit(-1);
	}
	if (!SetThreadContext(hThread, &context))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": SetThreadContext failed!\n";
		system("pause");
		exit(-1);
	}
	if (!CloseHandle(hThread))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": CloseHandle failed!\n";
		system("pause");
		exit(-1);
	}
}

void DebugEventHandler::start()
{
	if (!DebugActiveProcess(PVZ::Memory::processId))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": DebugActiveProcess failed!\n";
		system("pause");
		exit(-1);
	}
	if (!WaitForDebugEvent(&debugEvent, -1))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": WaitForDebugEvent failed!\n";
		system("pause");
		exit(-1);
	}
	if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": ContinueDebugEvent failed!\n";
		system("pause");
		exit(-1);
	}
}

bool DebugEventHandler::run(int ms)
{
	if (!WaitForDebugEvent(&debugEvent, ms))
	{
		return false;
	}
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
		{
			std::cout << "[ERROR] line " << __LINE__ << ": ContinueDebugEvent failed!\n";
			system("pause");
			exit(-1);
		}
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
	if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": ContinueDebugEvent failed!\n";
		system("pause");
		exit(-1);
	}
	if (!WaitForDebugEvent(&debugEvent, -1))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": WaitForDebugEvent failed!\n";
		system("pause");
		exit(-1);
	}
}

void DebugEventHandler::resume()
{
	if (!ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": ContinueDebugEvent failed!\n";
		system("pause");
		exit(-1);
	}
}

void DebugEventHandler::stop()
{
	if (!DebugActiveProcessStop(PVZ::Memory::processId))
	{
		std::cout << "[ERROR] line " << __LINE__ << ": DebugActiveProcessStop failed!\n";
		system("pause");
		exit(-1);
	}
}