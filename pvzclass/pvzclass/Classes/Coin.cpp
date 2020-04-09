#include "../PVZ.h"

PVZ::Coin::Coin(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xE4) + indexoraddress * 0xD8;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Coin::GetCollision(CollisionBox* collbox)
{
	collbox->X = NULL;
	collbox->Y = NULL;
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x10);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x14);
}

void PVZ::Coin::SetCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x10, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0x14, collbox->Height);
}

void PVZ::Coin::Collect()
{
	SETARG(__asm__Collect, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Collect));
}
