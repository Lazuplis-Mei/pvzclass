#include "../PVZ.h"

PVZ::Plant::Plant(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0xAC) + indexoraddress * MemSize;
}

byte __asm__Plant_memset[]
{
	MOV_PTR_EUX_ADD__EVX(REG_EBX, REG_EDI, 0x00BC),
	PUSH_EUX(REG_EAX),
	MOV_EUX(REG_EAX, 0),
	0x89, 0x3C, 0x18,
	ADD_EUX(REG_EAX, 4),
	CMP_EUX_DWORD(REG_EAX, 0),
	JNG(-14),
	POP_EUX(REG_EAX),
	JMPFAR(0)
};

void PVZ::Plant::SetMemSize(int NewSize = 0x14C, int NewCount = 1024)
{
	if (NewSize < 0x14C)
		return;
	Memory::WriteMemory<int>(0x407CC2, NewSize * NewCount);
	Memory::WriteMemory<int>(0x4109F6, NewSize);
	Memory::WriteMemory<int>(0x41BAED, NewSize);
	Memory::WriteMemory<int>(0x41BAFF, NewSize);
	Memory::WriteMemory<int>(0x41BB1E, NewSize);
	Memory::WriteMemory<int>(0x41C965, NewSize);
	Memory::WriteMemory<int>(0x41C971, NewSize);
	Memory::WriteMemory<int>(0x41C989, NewSize);
	Memory::WriteMemory<int>(0x41DE9D, NewSize);
	Memory::WriteMemory<int>(0x41DEAF, NewSize);
	Memory::WriteMemory<int>(0x41DEB6, NewSize - 4);
	Memory::WriteMemory<int>(0x41DF11, NewSize);
	Memory::WriteMemory<int>(0x41E5AA, NewSize);
	Memory::WriteMemory<int>(0x41E5B3, NewSize);
	Memory::WriteMemory<int>(0x41E5CD, NewSize);
	Memory::WriteMemory<int>(0x41E5D5, NewSize);
	Memory::WriteMemory<int>(0x438ACD, NewSize);
	Memory::WriteMemory<int>(0x438F34, NewSize);
	Memory::WriteMemory<int>(0x481CFD, NewSize);
	Memory::WriteMemory<int>(0x481D09, NewSize);
	Memory::WriteMemory<int>(0x481D2E, NewSize);
	Memory::WriteMemory<int>(0x48235E, NewSize);
	Memory::WriteMemory<int>(0x524DB6, NewSize);
	Memory::WriteMemory<int>(0x52CBC0, NewSize);
	Memory::WriteMemory<int>(0x530433, NewSize);
	Memory::WriteMemory<int>(0x5304A5, NewSize);
	Memory::WriteMemory<byte>(0x45DCA8, 0xE9);
	Memory::WriteMemory<int>(0x45DCA9, PVZ::Memory::Variable + 400 - 5 - 0x45DCA8);
	Memory::WriteMemory<byte>(0x45DCAD, NOP);
	SETARG(__asm__Plant_memset, 8) = 0x14C;
	SETARG(__asm__Plant_memset, 20) = NewSize - 4;
	SETARG(__asm__Plant_memset, 28) = 0x45DCAE - 5 - (Memory::Variable + 427);
	PVZ::Memory::WriteArray<byte>(PVZ::Memory::Variable + 400, STRING(__asm__Plant_memset));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationPart1()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x94);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationPart2()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x98);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationPart3()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x9C);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationPart4()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0xA0);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationEyeBlink()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0xA4);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationPotatoGlow()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0xA8);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Plant::GetAnimationSleep()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0xAC);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<Animation>(ID_INDEX(ID)));
}

void PVZ::Plant::Light(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0xB8, cs);
}

void PVZ::Plant::Flash(int cs)
{
	Memory::WriteMemory<int>(BaseAddress + 0xBC, cs);
}

void PVZ::Plant::SetSleeping(bool sleeping)
{
	SETARG(__asm__Plant_SetSleeping, 1) = BaseAddress;
	__asm__Plant_SetSleeping[6] = sleeping;
	Memory::Execute(STRING(__asm__Plant_SetSleeping));
}

void PVZ::Plant::CreateEffect()
{
	SETARG(__asm__CreateEffect, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__CreateEffect));
}

void PVZ::Plant::SetStatic()
{
	SETARG(__asm__SetStatic, 1) = PVZBASEADDRESS + 0x160;
	SETARG(__asm__SetStatic, 6) = BaseAddress;
	Memory::Execute(STRING(__asm__SetStatic));

}

void PVZ::Plant::Smash()
{
	SETARG(__asm__Smash, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Smash));
}

int PVZ::Plant::CalcLayer()
{
	SETARG(__asm__Plant_CalcLayer, 1) = BaseAddress;
	SETARG(__asm__Plant_CalcLayer, 19) = Memory::Variable;
	return(Memory::Execute(STRING(__asm__Plant_CalcLayer)));
}


void PVZ::Plant::MoveTo(int row, int column)
{
	SPT<Board> tmp_board = this->GetBoard();
	this->Row = row;
	this->Column = column;
	this->ImageX = tmp_board->GridToXPixel(row, column);
	this->ImageY = tmp_board->GridToYPixel(row, column);
	this->Layer = this->CalcLayer();
}

void PVZ::Plant::Remove()
{
	SETARG(__asm__Plant__Remove, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Plant__Remove));
	return;
}

SPT<PVZ::Projectile> PVZ::Plant::Shoot(int targetid)
{
	return(this->Shoot(targetid == -1 ? MotionType::None : MotionType::Track, targetid, false));
}

SPT<PVZ::Projectile> PVZ::Plant::Shoot(MotionType::MotionType motiontype, int targetid, bool special)
{
	if (special)
		__asm__Shoot[1] = 1;
	__asm__Shoot[3] = Row;
	if (targetid != -1)
	{
		SPT<Zombie> tmp = MKS<Zombie>(ID_INDEX(targetid));
		SETARG(__asm__Shoot, 5) = tmp->GetBaseAddress();
	}
	SETARG(__asm__Shoot, 10) = BaseAddress;
	SETARG(__asm__Shoot, 29) = Memory::Variable;
	if (Type == PlantType::Starfruit)
	{
		Memory::Execute(STRING(__asm__Shoot));
		return NULL;
	};
	SPT<Projectile> re = MKS<Projectile>(Memory::Execute(STRING(__asm__Shoot)));
	if (motiontype != MotionType::None) 
	{
		re->Motion = motiontype;
		if (motiontype == MotionType::Track && targetid != -1)
			re->TracktargetId = targetid;
	}
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

PVZ::Plant::MagnetItem::MagnetItem(int address)
{
	BaseAddress = address;
};

SPT<PVZ::Plant::MagnetItem> PVZ::Plant::GetMagnetItem(int num)
{
	return(MKS<PVZ::Plant::MagnetItem>(BaseAddress + 0xC8 + num * 0x14));
}
