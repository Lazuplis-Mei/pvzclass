#include "events.h"
#include <vector>

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
			InvokeEvent(new EventProjectileFire(x),true);
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
			InvokeEvent(new EventProjectileRemove(x),true);
	}
	ProjectileList.clear();
	ProjectileList = list;
}