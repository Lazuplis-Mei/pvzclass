#include "CoinRemoveEvent.h"

CoinRemoveEvent::CoinRemoveEvent()
{
	address = 0x432DD0;
}

#if defined(_WIN64)
void CoinRemoveEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Rsi);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#else
void CoinRemoveEvent::handle(CONTEXT& context)
{
	auto coin = std::make_shared<PVZ::Coin>(context.Esi);
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i](coin);
	}
}
#endif