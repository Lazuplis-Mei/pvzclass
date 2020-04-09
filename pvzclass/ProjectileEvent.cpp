#include "events.h"
#include <vector>
void EventHandler::InvokeProjectileFireEvent(Projectile* projectile)
{
	int lim = FunctionProjectileFireEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionProjectileFireEvent[i](projectile);
}
void EventHandler::InvokeProjectileRemoveEvent(Projectile * projectile)
{
	int lim = FunctionProjectileRemoveEvent.size();
	for (int i = 0; i < lim; i++)
		FunctionProjectileRemoveEvent[i](projectile);
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

void EventHandler::RegisterProjectileFireEvent(void function(Projectile*))
{
	FunctionProjectileFireEvent.push_back(function);
}
void EventHandler::RegisterProjectileRemoveEvent(void function(Projectile*))
{
	FunctionProjectileRemoveEvent.push_back(function);
}