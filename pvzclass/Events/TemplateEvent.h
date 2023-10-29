#pragma once
#include "BaseEvent.h"
#include <functional>

template <class FunctionType> class TemplateEvent : public BaseEvent
{
public:
	void addListener(FunctionType listener);
protected:
	std::vector<FunctionType> listeners;
};

template<class FunctionType>
void TemplateEvent<FunctionType>::addListener(FunctionType listener)
{
	listeners.push_back(listener);
}