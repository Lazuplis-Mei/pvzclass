#include "PVZ.h"

PVZ::Lawn::Lawn(int baseaddress)
{
	BaseAddress = baseaddress;
};

LawnType PVZ::Lawn::GetGridType(int row, int column)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		return Memory::ReadMemory<LawnType>(BaseAddress + 0x168 + 4 * (6 * column + row));
	return LawnTypeNone;
};

void PVZ::Lawn::SetGridType(int column, int row, LawnType type)
{
	if (row >= 0 && row < 6 && column >= 0 && column < 9)
		Memory::WriteMemory<LawnType>(BaseAddress + 0x168 + 4 * (6 * column + row), type);

};

RouteType PVZ::Lawn::GetRouteType(int route)
{
	if (route >= 0 && route < 6)
		return Memory::ReadMemory<RouteType>(BaseAddress + 0x5D8 + 4 * route);
	return RouteTypeNone;
};

void PVZ::Lawn::SetRouteType(int route, RouteType type)
{
	if (route >= 0 && route < 6)
		Memory::WriteMemory<RouteType>(BaseAddress + 0x5D8 + 4 * route, type);
};

