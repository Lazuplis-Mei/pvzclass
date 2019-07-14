#include "../PVZ.h"

PVZ::Zombie::Zombie(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x90) + indexoraddress * 0x15C;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Zombie::Light(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0x54, cs);
}

void PVZ::Zombie::GetCollision(CollisionBox* collbox)
{
	collbox->X = Memory::ReadMemory<int>(BaseAddress + 0x8C);
	collbox->Y = Memory::ReadMemory<int>(BaseAddress + 0x90);
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0x94);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0x98);
}

void PVZ::Zombie::SetCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x8C, collbox->X);
	Memory::WriteMemory<int>(BaseAddress + 0x90, collbox->Y);
	Memory::WriteMemory<int>(BaseAddress + 0x94, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0x98, collbox->Height);
}

void PVZ::Zombie::GetAttackCollision(CollisionBox* collbox)
{
	collbox->X = Memory::ReadMemory<int>(BaseAddress + 0x9C);
	collbox->Y = Memory::ReadMemory<int>(BaseAddress + 0xA0);
	collbox->Width = Memory::ReadMemory<int>(BaseAddress + 0xA4);
	collbox->Height = Memory::ReadMemory<int>(BaseAddress + 0xA8);
}

void PVZ::Zombie::SetAttackCollision(CollisionBox* collbox)
{
	Memory::WriteMemory<int>(BaseAddress + 0x9C, collbox->X);
	Memory::WriteMemory<int>(BaseAddress + 0xA0, collbox->Y);
	Memory::WriteMemory<int>(BaseAddress + 0xA4, collbox->Width);
	Memory::WriteMemory<int>(BaseAddress + 0xA8, collbox->Height);
}

void PVZ::Zombie::GetAccessoriesType1(AccessoriesType1* acctype1)
{
	acctype1->Type = Memory::ReadMemory<ZombieAccessoriesType1::ZombieAccessoriesType1>(BaseAddress + 0xC4);
	acctype1->Hp = Memory::ReadMemory<int>(BaseAddress + 0xD0);
	acctype1->MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xD4);
}

void PVZ::Zombie::SetAccessoriesType1(AccessoriesType1* acctype1)
{
	Memory::WriteMemory<ZombieAccessoriesType1::ZombieAccessoriesType1>(BaseAddress + 0xC4, acctype1->Type);
	Memory::WriteMemory<int>(BaseAddress + 0xD0, acctype1->Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xD4, acctype1->MaxHp);
}

void PVZ::Zombie::GetAccessoriesType2(AccessoriesType2* acctype2)
{
	acctype2->Type = Memory::ReadMemory<ZombieAccessoriesType2::ZombieAccessoriesType2>(BaseAddress + 0xD8);
	acctype2->Hp = Memory::ReadMemory<int>(BaseAddress + 0xDC);
	acctype2->MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xE0);
}

void PVZ::Zombie::SetAccessoriesType2(AccessoriesType2* acctype2)
{
	Memory::WriteMemory<ZombieAccessoriesType2::ZombieAccessoriesType2>(BaseAddress + 0xD8, acctype2->Type);
	Memory::WriteMemory<int>(BaseAddress + 0xDC, acctype2->Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xE0, acctype2->MaxHp);

}

void PVZ::Zombie::GetBodyHp(int* hp, int* maxhp)
{
	*hp = Memory::ReadMemory<int>(BaseAddress + 0xC8);
	*maxhp = Memory::ReadMemory<int>(BaseAddress + 0xCC);
}

void PVZ::Zombie::SetBodyHp(int hp, int maxhp)
{
	Memory::WriteMemory<int>(BaseAddress + 0xC8, hp);
	Memory::WriteMemory<int>(BaseAddress + 0xCC, maxhp);
}

PVZ::Animation* PVZ::Zombie::GetAnimation()
{
	return new Animation(Memory::ReadMemory<short>(BaseAddress + 0x118));
}

void PVZ::Zombie::Hit(int damge, DamageType::DamageType type)
{
	SETARG(__asm__Hit, 1) = BaseAddress;
	SETARG(__asm__Hit, 6) = type;
	SETARG(__asm__Hit, 11) = damge;
	Memory::Execute(STRING(__asm__Hit));
}

void PVZ::Zombie::Blast()
{
	SETARG(__asm__Blast, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Blast));
}

void PVZ::Zombie::Butter()
{
	SETARG(__asm__Butter, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Butter));
}

void PVZ::Zombie::SetAnimation(LPCSTR animName, byte animPlayArg)
{
	int Address = PVZ::Memory::AllocMemory();
	SETARG(__asm__Zombie__setAnimation, 1) = BaseAddress;
	__asm__Zombie__setAnimation[10] = animPlayArg;
	SETARG(__asm__Zombie__setAnimation, 12) = Address + 30;
	lstrcpyA((LPSTR)(__asm__Zombie__setAnimation + 30), animName);
	PVZ::Memory::WriteArray<byte>(Address, STRING(__asm__Zombie__setAnimation));
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xFE);
	PVZ::Memory::CreateThread(Address);
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xDB);
	PVZ::Memory::FreeMemory(Address);
}

