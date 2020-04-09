#include "../PVZ.h"

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

PVZ::Animation* PVZ::Plant::GetAnimationPart1()
{
	return new Animation(Memory::ReadMemory<short>(BaseAddress + 0x94));
}

PVZ::Animation* PVZ::Plant::GetAnimationPart2()
{
	return new Animation(Memory::ReadMemory<short>(BaseAddress + 0x98));
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

PVZ::Projectile* PVZ::Plant::Shoot(int targetid)
{
	__asm__Shoot[3] = Row;
	SETARG(__asm__Shoot, 10) = BaseAddress;
	SETARG(__asm__Shoot, 29) = Memory::Variable;
	if (Type == PlantType::Starfruit)
	{
		Memory::Execute(STRING(__asm__Shoot));
		return NULL;
	};
	Projectile* re = new Projectile(Memory::Execute(STRING(__asm__Shoot)));
	if (targetid == -1) 
	{ 
		return re;
	}
	re->Motion = MotionType::Track;
	re->DamageAbility = 15;
	re->TracktargetId = targetid;
	return re;
}

void PVZ::Plant::SetAnimation(LPCSTR animName, byte animPlayArg, int imagespeed)
{
	int Address = PVZ::Memory::AllocMemory();
	SETARG(__asm__Plant__setAnimation, 1) = BaseAddress;
	SETARG(__asm__Plant__setAnimation, 6) = imagespeed;
	__asm__Plant__setAnimation[13] = animPlayArg;
	SETARG(__asm__Plant__setAnimation, 15) = Address + 33;
	lstrcpyA((LPSTR)(__asm__Plant__setAnimation + 33), animName);
	PVZ::Memory::WriteArray<byte>(Address, STRING(__asm__Plant__setAnimation));
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xFE);
	PVZ::Memory::CreateThread(Address);
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xDB);
	PVZ::Memory::FreeMemory(Address);
}
