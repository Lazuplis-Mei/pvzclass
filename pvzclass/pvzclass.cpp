#include "pvzclass.h"
#include <iostream>

using namespace std;

int main()
{
	DWORD pid = ProcessOpener::Open();
	if (!pid) return 1;
	PVZ* pvz = new PVZ(pid);

	while (true)
	{
		int code = PVZ::Memory::ReadMemory<DWORD>(0x70000C);
		if (code == 1)
		{
			shared_ptr<PVZ::Zombie> zombie = make_shared<PVZ::Zombie>(PVZ::Memory::ReadMemory<DWORD>(0x700000));
			DamageType::DamageType type = (DamageType::DamageType)PVZ::Memory::ReadMemory<DWORD>(0x700004);
			int amount = PVZ::Memory::ReadMemory<DWORD>(0x700008);

			cout << ZombieType::ToString(zombie->Type) << " 收到了 " << amount << " 点伤害，类型为 " << DamageType::ToString(type) << endl;

			PVZ::Memory::WriteMemory<DWORD>(0x70000C, 0);
		}
	}

	delete pvz;
	return 0;
}
