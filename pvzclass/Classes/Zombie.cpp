#include "../PVZ.h"

PVZ::Zombie::Zombie(int indexoraddress)
{
	if (indexoraddress > 1024)
		BaseAddress = indexoraddress;
	else
		BaseAddress = Memory::ReadMemory<int>(PVZBASEADDRESS + 0x90) + indexoraddress * 0x15C;
}

void PVZ::Zombie::SetMemSize(int NewSize, int NewCount)
{
	if (NewSize < 0x15C)
		return;
	Memory::WriteMemory<int>(0x407CAA, NewSize * NewCount);

	byte __asm__Mem1[] = { ADD_EAX_DWORD(NewSize) };
	byte __asm__Mem2[] = { ADD_EUX_DWORD(REG_ESI, NewSize) };
	byte __asm__Mem3[] = { ADD_EUX_DWORD(REG_EDI, NewSize) };
	byte __asm__Mem4[] = { IMUL_EUX_EVX_DWORD(REG_EAX, REG_EAX, NewSize) };
	byte __asm__Mem5[] = { IMUL_EUX_EVX_DWORD(REG_ECX, REG_ECX, NewSize) };
	byte __asm__Mem6[] = { IMUL_EUX_EVX_DWORD(REG_EDX, REG_EDX, NewSize) };
	byte __asm__Mem7[] = { IMUL_EUX_EVX_DWORD(REG_ESI, REG_ESI, NewSize) };
	byte __asm__Mem8[] = { IMUL_EUX_EVX_DWORD(REG_EDI, REG_EDI, NewSize) };
	byte __asm__Mem9[] = { PUSHDWORD(NewSize - 4) };
	byte __asm__MemA[] = { 0x8D, 0xB5, INUMBER(NewSize) };

	Memory::WriteArray<byte>(0x41BB64, STRING(__asm__Mem3));
	Memory::WriteArray<byte>(0x41BB76, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x41BB8A, STRING(__asm__Mem3));
	Memory::WriteArray<byte>(0x41C802, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x41C904, STRING(__asm__Mem1));
	Memory::WriteArray<byte>(0x41C90F, STRING(__asm__Mem5));
	Memory::WriteArray<byte>(0x41C928, STRING(__asm__Mem1));
	Memory::WriteArray<byte>(0x41DDBB, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x41DDCD, STRING(__asm__Mem8));
	Memory::WriteArray<byte>(0x41DDD5, STRING(__asm__Mem9));
	Memory::WriteArray<byte>(0x41DE2F, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x41E4DE, STRING(__asm__Mem2));
	Memory::WriteArray<byte>(0x41E4E7, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x41E502, STRING(__asm__Mem5));
	Memory::WriteArray<byte>(0x41E50A, STRING(__asm__Mem2));
	Memory::WriteArray<byte>(0x4601B8, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x4602F6, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x4679E5, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x46D8E4, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x481D52, STRING(__asm__MemA));
	Memory::WriteArray<byte>(0x481D5E, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x481D78, STRING(__asm__Mem2));
	Memory::WriteArray<byte>(0x48226C, STRING(__asm__Mem7));
	Memory::WriteArray<byte>(0x527FB6, STRING(__asm__Mem8));
	Memory::WriteArray<byte>(0x52809A, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x5289AF, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x528A76, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x52C71B, STRING(__asm__Mem6));
	Memory::WriteArray<byte>(0x52CB27, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x52EF5E, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x52EFA2, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x52FAC9, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x52FB1C, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x530345, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x53037B, STRING(__asm__Mem5));
	Memory::WriteArray<byte>(0x5303C4, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x5303EF, STRING(__asm__Mem5));
	Memory::WriteArray<byte>(0x5304DE, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x5346CF, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x5352E8, STRING(__asm__Mem4));
	Memory::WriteArray<byte>(0x535364, STRING(__asm__Mem4));
}

void PVZ::Zombie::SetSpeed(float speed)
{
	Memory::WriteMemory<float>(BaseAddress + 0x34, speed);
	SETARG(__asm__Zombie__UpdateSpeed, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Zombie__UpdateSpeed));
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

PVZ::Zombie::AccessoriesType1 PVZ::Zombie::GetAccessoriesType1()
{
	AccessoriesType1 acctype1;
	acctype1.Type = Memory::ReadMemory<ZombieAccessoriesType1::ZombieAccessoriesType1>(BaseAddress + 0xC4);
	acctype1.Hp = Memory::ReadMemory<int>(BaseAddress + 0xD0);
	acctype1.MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xD4);
	return acctype1;
}

void PVZ::Zombie::SetAccessoriesType1(AccessoriesType1 acctype1)
{
	Memory::WriteMemory<ZombieAccessoriesType1::ZombieAccessoriesType1>(BaseAddress + 0xC4, acctype1.Type);
	Memory::WriteMemory<int>(BaseAddress + 0xD0, acctype1.Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xD4, acctype1.MaxHp);
}

PVZ::Zombie::AccessoriesType2 PVZ::Zombie::GetAccessoriesType2()
{
	AccessoriesType2 acctype2;
	acctype2.Type = Memory::ReadMemory<ZombieAccessoriesType2::ZombieAccessoriesType2>(BaseAddress + 0xD8);
	acctype2.Hp = Memory::ReadMemory<int>(BaseAddress + 0xDC);
	acctype2.MaxHp = Memory::ReadMemory<int>(BaseAddress + 0xE0);
	return acctype2;
}

void PVZ::Zombie::SetAccessoriesType2(AccessoriesType2 acctype2)
{
	Memory::WriteMemory<ZombieAccessoriesType2::ZombieAccessoriesType2>(BaseAddress + 0xD8, acctype2.Type);
	Memory::WriteMemory<int>(BaseAddress + 0xDC, acctype2.Hp);
	Memory::WriteMemory<int>(BaseAddress + 0xE0, acctype2.MaxHp);

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

SPT<PVZ::Animation> PVZ::Zombie::GetAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x118);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<PVZ::Animation>(ID_INDEX(ID)));
}

SPT<PVZ::Animation> PVZ::Zombie::GetSpecialHeadAnimation()
{
	int ID = Memory::ReadMemory<int>(BaseAddress + 0x144);
	return ((ID_RANK(ID) == 0) ? nullptr : MKS<PVZ::Animation>(ID_INDEX(ID)));
}

void PVZ::Zombie::SetSpecialHeadAnimation(SPT<PVZ::Animation> anim)
{
	Memory::WriteMemory<int>(BaseAddress + 0x144, anim->Id);
}

void PVZ::Zombie::Hit(int damage, DamageType::DamageType type)
{
	PVZ::Zombie::Hit(damage, (DamageFlags)type);
}

void PVZ::Zombie::Hit(int damage, DamageFlags flags)
{
	SETARG(__asm__Hit, 1) = BaseAddress;
	SETARG(__asm__Hit, 6) = flags;
	SETARG(__asm__Hit, 11) = damage;
	Memory::Execute(STRING(__asm__Hit));
}

void PVZ::Zombie::HitBody(int damage, DamageType::DamageType type)
{
	PVZ::Zombie::HitBody(damage, (DamageFlags)type);
}

void PVZ::Zombie::HitBody(int damage, DamageFlags flags)
{
	SETARG(__asm__HitBody, 1) = flags;
	SETARG(__asm__HitBody, 6) = damage;
	SETARG(__asm__HitBody, 11) = BaseAddress;
	Memory::Execute(STRING(__asm__HitBody));
}

void PVZ::Zombie::Blast()
{
	SETARG(__asm__Blast, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Blast));
}

void PVZ::Zombie::Butter(int countdown = 400)
{
	int temp = FixedCountdown;
	SETARG(__asm__Butter, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Butter));
	FixedCountdown = max(temp, countdown);
}

void PVZ::Zombie::Decelerate(int countdown = 1000)
{
	int temp = DecelerateCountdown;
	SETARG(__asm__Decelerate, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Decelerate));
	DecelerateCountdown = max(temp, countdown);
}

void PVZ::Zombie::Froze(int countdown = 300)
{
	Memory::WriteMemory<byte>(0x532493, 0);
	Memory::WriteMemory<byte>(0x5319E5, 112);//无视魅惑
	int temp = FrozenCountdown, temp2 = DecelerateCountdown;
	SETARG(__asm__Froze, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Froze));
	Memory::WriteMemory<byte>(0x532493, 20);
	Memory::WriteMemory<byte>(0x5319E5, 117);
	DecelerateCountdown = temp2;
	FrozenCountdown = max(temp, countdown);
}

void PVZ::Zombie::Hypnotize()
{
	SETARG(__asm__Hypnotize, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Hypnotize));
}

void PVZ::Zombie::Remove()
{
	SETARG(__asm__Zombie__Remove, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Zombie__Remove));
}

void PVZ::Zombie::RemoveWithLoot()
{
	SETARG(__asm__Zombie__RemoveWithLoot, 1) = BaseAddress;
	Memory::Execute(STRING(__asm__Zombie__RemoveWithLoot));
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

void PVZ::Zombie::EquipBucket(int shield)
{
	if (this->GetAccessoriesType1().Type)
		return;
	this->GetAnimation()->AssignRenderGroupToPrefix(0, "anim_bucket");
	this->SetAccessoriesType1({ ZombieAccessoriesType1::Bucket, shield, shield });
}

void PVZ::Zombie::EquipCone(int shield)
{
	if (this->GetAccessoriesType1().Type)
		return;
	this->GetAnimation()->AssignRenderGroupToPrefix(0, "anim_cone");
	this->SetAccessoriesType1({ ZombieAccessoriesType1::RoadCone, shield, shield });
}

void PVZ::Zombie::ReanimShowPrefix(const char* TrackName, int renderGroup)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, TrackName, std::strlen(TrackName) + 1);
	SETARG(__asm__Zombie_ReanimShowPrefix, 1) = BaseAddress;
	SETARG(__asm__Zombie_ReanimShowPrefix, 6) = renderGroup;
	SETARG(__asm__Zombie_ReanimShowPrefix, 11) = PVZ::Memory::Variable + 100;
	Memory::Execute(STRING(__asm__Zombie_ReanimShowPrefix));
}

bool PVZ::Zombie::canDecelerate()
{
	Memory::WriteMemory<byte>(0x5319E5, 112);//无视魅惑
	SETARG(__asm__CanDecelerate, 1) = BaseAddress;
	SETARG(__asm__CanDecelerate, 19) = Memory::Variable;
	return(Memory::Execute(STRING(__asm__CanDecelerate)) == 1);
	Memory::WriteMemory<byte>(0x5319E5, 117);
}

bool PVZ::Zombie::canFroze()
{
	if (!this->canDecelerate())
		return(false);
	ZombieState::ZombieState state = this->State;
	switch (state)
	{
	case ZombieState::POLE_VALUTING_JUMPPING:
	case ZombieState::DOPHIN_JUMP_IN_POOL:
	case ZombieState::DOPHIN_JUMP:
	case ZombieState::SNORKEL_JUMP_IN_THE_POOL:
	case ZombieState::IMP_FLYING:
	case ZombieState::IMP_LANDING:
	case ZombieState::BALLOON_FLYING:
	case ZombieState::BALLOON_FALLING:
	case ZombieState::JACKBOX_POP:
	case ZombieState::BOBSLED_GETOFF:
	case ZombieState::SQUASH_RISE:
	case ZombieState::SQUASH_FALL:
	case ZombieState::SQUASH_SMASH:
		return(false);
	}
	if (state >= 20 && state <= 28)
		return(false);
	if (this->Type == ZombieType::BungeeZombie && state != ZombieState::BUNGEE_IDLE_AFTER_DROP)
		return(false);
	return(true);
}

bool PVZ::Zombie::EffectedBy(DamageRangeFlags range, bool usepvzfunc)
{
	if (usepvzfunc)
	{
		SETARG(__asm__Zombie_EffectedBy, 1) = BaseAddress;
		__asm__Zombie_EffectedBy[6] = range;
		SETARG(__asm__Zombie_EffectedBy, 21) = Memory::Variable;
		return(Memory::Execute(STRING(__asm__Zombie_EffectedBy)) == 1);
	}
	else
	{
		ZombieType::ZombieType type = this->Type;
		ZombieState::ZombieState state = this->State;

		if ((range & DRF_DYING) == 0)
		{
			if (this->NotExist)
				return(false);
			if (state == ZombieState::DYING
				|| state == ZombieState::DYING_FROM_INSTANT_KILL
				|| state == ZombieState::DYING_FROM_LAWNMOWER)
				return(false);
		}
		bool intendHypnotized = range & DRF_HYPNOTIZED;
		if (this->Hypnotized ^ intendHypnotized)
			return(false);
		if (type == ZombieType::BungeeZombie)
		{
			if (state != ZombieState::BUNGEE_IDLE_AFTER_DROP && state != ZombieState::BUNGEE_GRAB)
				return(false);
		}
		if (this->ZombieHeight == 9)
			return(false);
		if (type == ZombieType::DrZomboss)
		{
			SPT<Animation> anim = this->GetAnimation();
			if (state == ZombieState::ZOMBOSS_FALL && anim->CycleRate < 0.5)
				return(false);
			if (state == ZombieState::ZOMBOSS_RISE && anim->CycleRate > 0.5)
				return(false);
			if (state != ZombieState::ZOMBOSS_DOWN
				&& state != ZombieState::ZOMBOSS_PREPARE_RISE
				&& state != ZombieState::ZOMBOSS_BALL)
					return(false);
		}
		//if (type == ZombieType::ZombieBobsledTeam && )
			//return(false);
		if (state == ZombieState::POLE_VALUTING_JUMPPING
			|| state == ZombieState::IMP_FLYING
			|| state == ZombieState::DIGGER_DRILL
			|| state == ZombieState::DIGGER_LOST_DIG
			|| state == ZombieState::DIGGER_LANDING
			|| state == ZombieState::DOPHIN_JUMP_IN_POOL
			|| state == ZombieState::DOPHIN_JUMP
			|| state == ZombieState::SNORKEL_JUMP_IN_THE_POOL
			|| state == ZombieState::BALLOON_FALLING
			|| state == ZombieState::RISING_FROM_GROUND
			|| state == ZombieState::BOBSLED_GETOFF
			|| state == ZombieState::BACKUP_SPAWNING)
				return(range & DRF_OFF_GROUND);

		//)if (this->mZombieType == ZombieType::BOBSLED

		bool submerged = type == ZombieType::SnorkedZombie && this->InWater && !this->Eating;
		if ((range & DRF_SUBMERGED) != 0 && submerged)
			return(true);

		if((range & DRF_UNDERGROUND) != 0
			&& state == ZombieState::DIGGER_DIG)
				return(true);

		bool flying = state == ZombieState::BALLOON_FLYING || state == ZombieState::BALLOON_FALLING;
		if((range & DRF_FLYING) != 0 && flying)
			return(true);
		
		if (range & DRF_GROUND && !flying && !submerged && state != ZombieState::DIGGER_DIG)
			return(true);

		return(false);
	}
}
