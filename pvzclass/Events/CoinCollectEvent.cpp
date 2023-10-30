#include "CoinCollectEvent.h"

CoinCollectEvent::CoinCollectEvent()
{
	address = 0x432060;
}

#if defined(_WIN64)
void CoinCollectEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Rcx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#else
void CoinCollectEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Ecx);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#endif