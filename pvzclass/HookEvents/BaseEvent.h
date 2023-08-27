#pragma once
#include "../PVZ.h"
#include <vector>
#include <functional>

template <class FunctionType> class BaseEvent
{
protected:
	std::vector<FunctionType> listeners;
public:
	virtual void start() = 0;
	void addListener(FunctionType listener);
	virtual void run() = 0;
	bool removeListener(int index);
	virtual void end() = 0;
};

template<class FunctionType>
void BaseEvent<FunctionType>::addListener(FunctionType listener)
{
	listeners.push_back(listener);
}

template<class FunctionType>
bool BaseEvent<FunctionType>::removeListener(int index)
{
	if (index >= listeners.size()) return false;
	listeners.erase(listeners.begin() + index);
	return true;
}