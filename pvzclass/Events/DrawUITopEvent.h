#pragma once
#include "TemplateEvent.h"

// 绘制顶层UI事件
// 参数：Graphic指针
// 无返回值
class DrawUITopEvent : public TemplateEvent<std::function<
	void(std::shared_ptr<PVZ::Graphics>)>>
{
public:
	DrawUITopEvent();
	void handle(CONTEXT& context) override;
};

DrawUITopEvent::DrawUITopEvent()
{
	address = 0x4172F6;
}

void DrawUITopEvent::handle(CONTEXT& context)
{
	int eax = context.Eax;
	std::cout << eax << std::endl;
	int address = PVZ::Memory::ReadPointer(eax, 0);
	std::cout << address << std::endl;
	auto graphics = std::make_shared<PVZ::Graphics>(address);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](graphics);
	}
}