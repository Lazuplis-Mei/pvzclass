#pragma once
#include "../PVZ.h"
#include "BaseEvent.h"
#include <vector>

extern bool eventHandled = true;

inline void eventHandlerStart(DEBUG_EVENT& debugEvent)
{
	DebugActiveProcess(PVZ::Memory::processId);
	WaitForDebugEvent(&debugEvent, -1);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
}

// 返回hThread，0则不需要调用handle()
inline void eventHandlerRun(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE& hThread, int ms)
{
	if (!eventHandled)
	{
		if (hThread > 0) CloseHandle(hThread);
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	}
	eventHandled = false;
	WaitForDebugEvent(&debugEvent, ms);
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
		return;
	}
	context.ContextFlags = CONTEXT_ALL;
	hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	if (hThread == 0)
	{
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
		return;
	}
	GetThreadContext(hThread, &context);
	context.Eip--;
	return;
}

inline void eventHandlerStop()
{
	DebugActiveProcessStop(PVZ::Memory::processId);
}