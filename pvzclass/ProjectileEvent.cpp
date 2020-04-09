#include "events.h"
#include <vector>
void EventHandler::InvokeProjectileFireEvent(Projectile* projectile)
{
	int lim = FunctionProjectileFireEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileFireEventHigh[i](projectile))
			return; 
	lim = FunctionProjectileFireEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileFireEventMid[i](projectile))
			return;
	lim = FunctionProjectileFireEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileFireEventLow[i](projectile))
			return;
}
void EventHandler::InvokeProjectileRemoveEvent(Projectile * projectile)
{
	int lim = FunctionProjectileRemoveEventHigh.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileRemoveEventHigh[i](projectile))
			return; 
	lim = FunctionLevelStartEventMid.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileRemoveEventMid[i](projectile))
			return;
	lim = FunctionProjectileRemoveEventLow.size();
	for (int i = 0; i < lim; i++)
		if (FunctionProjectileRemoveEventLow[i](projectile))
			return;
}
std::vector<Projectile*> EventHandler::GetAllProjectiles()
{
	std::vector<Projectile*> rt;
	int maxnum = PVZ::Memory::ReadMemory<int>(pvz->BaseAddress + 0xCC);
	for (int i = 0; i < maxnum; i++)
		if (!PVZ::Memory::ReadPointer(pvz->BaseAddress + 0xC8, 0x50 + 0x94 * i))
			rt.push_back(new PVZ::Projectile(i));
	return rt;
}
void EventHandler::UpdateProjectiles()
{
	if (!Address)
	{
		if (ProjectileList.size())
			ProjectileList.clear();
		return;
	}
	std::vector<Projectile*> list = GetAllProjectiles();
	int nown = list.size();
	int lastn = ProjectileList.size();
	for (int i = 0; i < nown; i++)
	{
		bool ok = 1;
		Projectile* x = list[i];
		for (int j = 0; j < lastn; j++)
			if (x->BaseAddress == ProjectileList[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
			InvokeProjectileFireEvent(x);
	}
	for (int i = 0; i < lastn; i++)
	{
		bool ok = 1;
		Projectile* x = ProjectileList[i];
		for (int j = 0; j < nown; j++)
			if (x->BaseAddress == list[j]->BaseAddress)
			{
				ok = 0;
				break;
			}
		if (ok)
			InvokeProjectileRemoveEvent(x);
	}
	ProjectileList.clear();
	ProjectileList = list;
}

void EventHandler::RegisterProjectileFireEvent(bool function(Projectile*), int level)
{
	if (level == Event_Low)
		FunctionProjectileFireEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionProjectileFireEventMid.push_back(function);
	else if (level == Event_High)
		FunctionProjectileFireEventHigh.push_back(function);
}
void EventHandler::RegisterProjectileRemoveEvent(bool function(Projectile*), int level)
{
	if (level == Event_Low)
		FunctionProjectileRemoveEventLow.push_back(function);
	else if (level == Event_Mid)
		FunctionProjectileRemoveEventMid.push_back(function);
	else if (level == Event_High)
		FunctionProjectileRemoveEventHigh.push_back(function);
}