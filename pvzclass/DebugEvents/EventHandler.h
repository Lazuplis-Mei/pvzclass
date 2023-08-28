#pragma once
#include "../PVZ.h"
#include "BaseEvent.h"
#include <vector>

inline void eventHandlerStart(DEBUG_EVENT& debugEvent)
{
	DebugActiveProcess(PVZ::Memory::processId);
	WaitForDebugEvent(&debugEvent, -1);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
}

// 返回hThread，0则不需要调用handle()
inline HANDLE eventHandlerRun(DEBUG_EVENT& debugEvent, CONTEXT& context, int ms)
{
	WaitForDebugEvent(&debugEvent, ms);
	if (debugEvent.dwDebugEventCode != EXCEPTION_DEBUG_EVENT)
	{
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
		return 0;
	}
	context.ContextFlags = CONTEXT_ALL;
	HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, true, debugEvent.dwThreadId);
	if (hThread == 0)
	{
		ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
		return 0;
	}
	GetThreadContext(hThread, &context);
	context.Eip--;
	return hThread;
}

inline void eventHandlerStop()
{
	DebugActiveProcessStop(PVZ::Memory::processId);
}