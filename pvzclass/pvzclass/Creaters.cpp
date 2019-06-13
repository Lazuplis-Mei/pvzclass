#include "Creaters.h"

byte __asm__CreateZombie[34]
{
	MOV_ECX_PTR_ADDR(0),
	MOV_EAX(0),
	CREATEZOMBIE,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

byte __asm__CreateZombie__pieces1[6]
{
	MOV_EAX_EBX,
	POP_EBX,
	RETN(8),
};

PVZ::Zombie* CreateZombie(ZombieType::ZombieType type, int row, byte column)
{
	PVZ::Memory::WriteArray(0x42A209, STRING(__asm__CreateZombie__pieces1));
	PVZ::Memory::WriteMemory<short>(0x42A1E4, makeshort(JMP(0x23)));
	PVZ::Memory::WriteMemory<short>(0x42A196, makeshort(JMP(0x71)));
	SETARG(__asm__CreateZombie, 2) = PVZBASEADDRESS + 0x160;
	SETARG(__asm__CreateZombie, 7) = row;
	__asm__CreateZombie[12] = column;
	__asm__CreateZombie[14] = (byte)type;
	SETARG(__asm__CreateZombie, 29) = PVZ::Memory::Variable;
	return new PVZ::Zombie(PVZ::Memory::Execute(STRING(__asm__CreateZombie)));
}
