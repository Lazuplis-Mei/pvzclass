#pragma once
#include "TemplateEvent.h"

// 植物重新装填事件
// 参数：触发事件的植物，生效倒计时
// 返回值：修改后的倒计时
// 监听器之间串联修改
// 注：植物每隔一段时间就重新装填，此时如果发现僵尸则射击
// 生效倒计时默认为生效间隔减去一个[0,14]的随机数
class PlantReloadEvent : public TemplateEvent<std::function<
	int(std::shared_ptr<PVZ::Plant>, int)>>
{
public:
	PlantReloadEvent();
	void handle(CONTEXT& context) override;
};

PlantReloadEvent::PlantReloadEvent()
{
	address = 0x45F8C4;
}

void PlantReloadEvent::handle(CONTEXT& context)
{
	auto plant = std::make_shared<PVZ::Plant>(context.Esi);
	int cd = context.Ecx;
	for (int i = 0; i < listeners.size(); i++)
	{
		cd = listeners[i](plant, cd);
	}
	context.Ecx = cd;
}
