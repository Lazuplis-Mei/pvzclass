#pragma once
#include "../PVZ.h"
#include <vector>
#include <functional>

template <class FunctionType> class BaseEvent
{
public:
	void start();
	// 处理这个事件，true为成功处理，false为跳过处理
	//（因为不一定中断是由该事件引发的）
	// 调用前需调用 eventHandlerRun()
	virtual bool handle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread) = 0;
	void end();
	void addListener(FunctionType listener);
protected:
	DWORD address;
	BYTE raw;
	std::vector<FunctionType> listeners;
	void afterHandle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread);
};

template<class FunctionType>
void BaseEvent<FunctionType>::addListener(FunctionType listener)
{
	listeners.push_back(listener);
}

template<class FunctionType>
void BaseEvent<FunctionType>::start()
{
	raw = PVZ::Memory::ReadMemory<BYTE>(address);
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
}

template<class FunctionType>
void BaseEvent<FunctionType>::afterHandle(DEBUG_EVENT& debugEvent, CONTEXT& context, HANDLE hThread)
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
	context.EFlags |= 0x100;
	SetThreadContext(hThread, &context);
	CloseHandle(hThread);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
	ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, DBG_CONTINUE);
}

template<class FunctionType>
void BaseEvent<FunctionType>::end()
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
}