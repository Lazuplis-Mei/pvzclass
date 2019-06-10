#include "PVZ.h"

PVZ::Plant::Plant(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xAC) + indexoraddress * 0x14C;
#if _DEBUG
	DebugType = Type;
#endif
}

void PVZ::Plant::GetAnimationPart1(PVZ::Animation* animation)
{
	animation = new Animation(Memory::ReadMemory<short>(BaseAddress + 0x94));
}

void PVZ::Plant::GetAnimationPart2(PVZ::Animation* animation)
{
	animation = new Animation(Memory::ReadMemory<short>(BaseAddress + 0x98));
}

void PVZ::Plant::Light(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0xB8, cs);
}

void PVZ::Plant::Flash(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0xBC, cs);
}

void PVZ::Plant::CreateEffect()
{
	SETARG(__asm__CreateEffect, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__CreateEffect));
}

void PVZ::Plant::SetStatic()
{
	SETARG(__asm__SetStatic, 1) = PVZBASEADDRESS + 0x160;
	SETARG(__asm__SetStatic, 6) = BaseAddress;;
	Memory::Execute(STRING(__asm__SetStatic));

}

void PVZ::Plant::Shoot(PVZ::Projectile* pro, int targetid)
{
	__asm__Shoot[3] = Row;
	SETARG(__asm__Shoot, 10) = BaseAddress;
	SETARG(__asm__Shoot, 29) = Memory::Variable;
	if (Type == Starfruit)
	{
		Memory::Execute(STRING(__asm__Shoot));
		return;
	};
	Projectile* re = new Projectile(Memory::Execute(STRING(__asm__Shoot)));
	if (targetid == -1) 
	{ 
		pro = re;
		return;
	}
	re->Motion = Track;
	re->DamageAbility = 15;
	re->TracktargetId = targetid;
	pro = re;
}
