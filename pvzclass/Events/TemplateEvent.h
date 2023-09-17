#pragma once
#include "../PVZ.h"
#include "EventHandler.h"
#include <iostream>
#include <vector>
#include <functional>

template <class FunctionType> class TemplateEvent
{
public:
	void start();
	void addListener(FunctionType listener);
	// 处理这个事件，返回是否是该事件引发的中断
	virtual bool handle(EventHandler handler) = 0;
	void end();
protected:
	DWORD address;
	BYTE raw;
	std::vector<FunctionType> listeners;
	void afterHandle(EventHandler handler);
};

template<class FunctionType>
void TemplateEvent<FunctionType>::addListener(FunctionType listener)
{
	listeners.push_back(listener);
}

template<class FunctionType>
void TemplateEvent<FunctionType>::start()
{
	raw = PVZ::Memory::ReadMemory<BYTE>(address);
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
}

template<class FunctionType>
void TemplateEvent<FunctionType>::afterHandle(EventHandler handler)
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
	handler.singleStep();
	PVZ::Memory::WriteMemory<BYTE>(address, 0xCC);
}

template<class FunctionType>
void TemplateEvent<FunctionType>::end()
{
	PVZ::Memory::WriteMemory<BYTE>(address, raw);
}