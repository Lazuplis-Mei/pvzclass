#include "Creaters.h"
#include <iostream>

byte __asm__CreateZombie[34]
{
	MOV_ECX_PTR_ADDR(0),
	MOV_EAX(0),
	CREATEZOMBIE,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

byte __asm__CreateZombie__pieces[6]
{
	MOV_EAX_EBX,
	POP_EBX,
	RETN(8),
};

PVZ::Zombie* Creater::CreateZombie(ZombieType::ZombieType type, int row, byte column)
{
	PVZ::Memory::WriteArray(0x42A209, STRING(__asm__CreateZombie__pieces));
	PVZ::Memory::WriteMemory<short>(0x42A1E4, makeshort(JMP(0x23)));
	PVZ::Memory::WriteMemory<short>(0x42A196, makeshort(JMP(0x71)));
	SETARG(__asm__CreateZombie, 2) = PVZBASEADDRESS + 0x160;
	SETARG(__asm__CreateZombie, 7) = row;
	__asm__CreateZombie[12] = column;
	__asm__CreateZombie[14] = type;
	SETARG(__asm__CreateZombie, 29) = PVZ::Memory::Variable;
	return new PVZ::Zombie(PVZ::Memory::Execute(STRING(__asm__CreateZombie)));
}

byte __asm__CreatePlant[35]
{
	MOV_EAX(0),
	CREATEPLANT,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

PVZ::Plant* Creater::CreatePlant(PlantType::PlantType type, int row, byte column, BOOLEAN imitative)
{
	if (imitative)__asm__CreatePlant[6] = type;
	__asm__CreatePlant[8] = imitative ? PlantType::Imitater : type;
	__asm__CreatePlant[10] = column;
	SETARG(__asm__CreatePlant, 1) = row;
	SETARG(__asm__CreatePlant, 12) = PVZBASEADDRESS;
	SETARG(__asm__CreatePlant, 30) = PVZ::Memory::Variable;
	return new PVZ::Plant(PVZ::Memory::Execute(STRING(__asm__CreatePlant)));
}

byte __asm__CreateProjectile[47]
{
	MOV_EAX(0),
	CREATEPROJECTILE,
	MOV_PTR_EAX_ADD(0x74,0xB),
	MOV_PTR_ADDR_EAX(0),
	RET,
};

PVZ::Projectile* Creater::CreateProjectile(ProjectileType::ProjectileType type, byte row, int x)
{
	SETARG(__asm__CreateProjectile, 1) = PVZBASEADDRESS;
	__asm__CreateProjectile[6] = type;
	__asm__CreateProjectile[8] = row;
	SceneType::SceneType scene = PVZ::Memory::ReadMemory<SceneType::SceneType>(PVZBASEADDRESS + 0x554C);
	bool sixroute = (scene == SceneType::Pool) || (scene == SceneType::Fog);
	int y = sixroute ? 94 + 86 * row : 90 + 100 * row;
	SETARG(__asm__CreateProjectile, 12) = y;
	SETARG(__asm__CreateProjectile, 17) = x;
	SETARG(__asm__CreateProjectile, 42) = PVZ::Memory::Variable;
	return new PVZ::Projectile(PVZ::Memory::Execute(STRING(__asm__CreateProjectile)));
}

byte __asm__CreateProjectile2[84]
{
	MOV_EAX(0),
	CREATEPROJECTILE,
	MOV_PTR_EAX_ADD(0x58,7),
	MOV_PTR_EAX_ADD(0x74,0xB),
	FILD_PTR(0),
	FDIV_PTR(0),
	FSTP_PTR_EAX_ADD(0x3C),
	FILD_PTR(0),
	FDIV_PTR(0),
	FSTP_PTR_EAX_ADD(0x40),
	MOV_PTR_ADDR_EAX(0),
	RET,
};

byte __asm__CreatePortalpieces1[10]
{
	MOV_ECX(4),
	JMPFAR(0),
};

byte __asm__CreatePortalpieces2[15]
{
	MOV_PTR_EAX_ADD_V_ECX(0x14),
	MOV_PTR_EAX_ADD_V_V(0x1C,0x54B78),
	JMPFAR(0),
};

void Creater::AsmInit()
{
	SETARG(__asm__CreateProjectile2, 50) = PVZ::Memory::Variable + 8;
	SETARG(__asm__CreateProjectile2, 56) = PVZ::Memory::Variable + 4;
	SETARG(__asm__CreateProjectile2, 65) = PVZ::Memory::Variable + 12;
	SETARG(__asm__CreateProjectile2, 71) = PVZ::Memory::Variable + 4;
	SETARG(__asm__CreateProjectile2, 79) = PVZ::Memory::Variable;
	PVZ::Memory::WriteArray<byte>(PVZ::Memory::Variable + 16, STRING(__asm__CreateProjectile2));
	//protal
	SETARG(__asm__CreatePortalpieces1, 6) = PVZ::Memory::Variable + 200 - 5 - 0x427071;
	PVZ::Memory::WriteArray<byte>(0x42706C, STRING(__asm__CreatePortalpieces1));
	SETARG(__asm__CreatePortalpieces2, 11) = 0x427076 - 5 - (PVZ::Memory::Variable + 510);
	PVZ::Memory::WriteArray<byte>(PVZ::Memory::Variable + 200, STRING(__asm__CreatePortalpieces2));
}

PVZ::Projectile* Creater::CreateProjectile(ProjectileType::ProjectileType type, int x, int y, float angle, float speed)
{
	angle = angle / 180 * PI;
	int xspeed = (int)(sin(angle) * speed * 10000);
	int yspeed = (int)(-cos(angle) * speed * 10000);
	PVZ::Memory::WriteMemory<float>(PVZ::Memory::Variable + 4, 10000.0f);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 8, xspeed);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 12, yspeed);
	PVZ::Memory::WriteMemory<byte>(PVZ::Memory::Variable + 22, type);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 28, y);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 33, x);
	xytorc(&x, &y);
	PVZ::Memory::WriteMemory<byte>(PVZ::Memory::Variable + 24, x);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 17, PVZBASEADDRESS);
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xFE);
	PVZ::Memory::CreateThread(PVZ::Memory::Variable + 16);
	PVZ::Memory::WriteMemory<byte>(0x552014, 0xDB);
	return new PVZ::Projectile(PVZ::Memory::ReadMemory<int>(PVZ::Memory::Variable));
}

byte __asm__CreateCoin[38]
{
	MOV_ECX(0),
	CREATECOIN,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

PVZ::Coin* Creater::CreateCoin(CoinType::CoinType type, int x, int y, CoinMotionType::CoinMotionType motion)
{
	SETARG(__asm__CreateCoin, 1) = PVZBASEADDRESS;
	__asm__CreateCoin[6] = motion;
	__asm__CreateCoin[8] = type;
	SETARG(__asm__CreateCoin, 10) = x;
	SETARG(__asm__CreateCoin, 15) = y;
	SETARG(__asm__CreateCoin, 33) = PVZ::Memory::Variable;
	return new PVZ::Coin(PVZ::Memory::Execute(STRING(__asm__CreateCoin)));
}

byte __asm__ResetLawnmover[19]
{
	RESETLAWNMOVER,
	RET,
};

void Creater::ResetLawnmover(PVZ* pvz)
{
	PVZ::Memory::AllAccess(0x679BF8);
	PVZ::Memory::WriteMemory<float>(0x679BF8, -21.0f);
	PVZ::Memory::WriteMemory<short>(0x40BC98, makeshort(JMP(0x60)));
	PVZ::Memory::WriteMemory<byte>(0x40BD17, 1);
	SETARG(__asm__ResetLawnmover, 1) = PVZBASEADDRESS;
	PVZ::Lawnmover* lawnmovers[18];
	int len = pvz->GetAllLawnmovers(lawnmovers);
	for (int i = 0; i < len; i++)
		lawnmovers[i]->NotExist = true;
	PVZ::Memory::Execute(STRING(__asm__ResetLawnmover));
	PVZ::Memory::WriteMemory<float>(0x679BF8, -160.0f);
	PVZ::Memory::WriteMemory<short>(0x40BC98, makeshort(JNZ(9)));
	PVZ::Memory::WriteMemory<byte>(0x40BD17, 0);
}

byte __asm__CreateGriditem[24]
{
	MOV_ESI(0),
	CREATEGRDITEM,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

PVZ::Griditem* Creater::CreateGriditem()
{
	SETARG(__asm__CreateGriditem, 1) = PVZBASEADDRESS + 0x11C;
	SETARG(__asm__CreateGriditem, 19) = PVZ::Memory::Variable;
	return new PVZ::Griditem(PVZ::Memory::Execute(STRING(__asm__CreateGriditem)));
}

byte __asm__CreateGrave[30]
{
	PUSH_PTR(0),
	MOV_EDI(0),
	MOV_EBX(0),
	CREATEGRAVE,
	RET,
};

void Creater::CreateGrave(int row, int column)
{
	SETARG(__asm__CreateGrave, 2) = PVZBASEADDRESS + 0x160;
	SETARG(__asm__CreateGrave, 7) = row;
	SETARG(__asm__CreateGrave,12) = column;
	PVZ::Memory::Execute(STRING(__asm__CreateGrave));
}

PVZ::Crater* Creater::CreateCrater(int row, int column, int duration)
{
	PVZ::Crater* crater = new PVZ::Crater(CreateGriditem()->BaseAddress);
	crater->Row = row;
	crater->Column = column;
	crater->Layer = crater->Column * 0x2710 + 0x49ED0;
	crater->DisappearCountdown = duration;
	crater->Type = GriditemType::Crater;
	return crater;
}

byte __asm__CreateLadder[31]
{
	MOV_EAX(0),
	MOV_EDI(0),
	CREATELADDER,
	MOV_PTR_ADDR_EAX(0),
	RET,
};

PVZ::Griditem* Creater::CreateLadder(int row, byte column)
{
	SETARG(__asm__CreateLadder, 1) = PVZBASEADDRESS;
	SETARG(__asm__CreateLadder, 6) = row;
	__asm__CreateLadder[11] = column;
	SETARG(__asm__CreateLadder, 26) = PVZ::Memory::Variable;;
	return new PVZ::Griditem(PVZ::Memory::Execute(STRING(__asm__CreateLadder)));
}

PVZ::Vase* Creater::CreateVase(int row, int column, VaseContent::VaseContent content, VaseSkin::VaseSkin skin, ZombieType::ZombieType zombie, PlantType::PlantType plant, int sun)
{
	PVZ::Vase* vase = new PVZ::Vase(CreateGriditem()->BaseAddress);
	vase->Row = row;
	vase->Column = column;
	vase->Layer = vase->Column * 0x2710 + 0x49ED0;
	vase->Type = GriditemType::Vase;
	vase->Skin = skin;
	vase->ContentZombie = zombie;
	vase->ContentPlant = plant;
	vase->Content = content;
	vase->Sun = sun;
	return vase;
}

PVZ::Vase* Creater::CreateVase(VaseCreateInfo vaseinfo)
{
	return CreateVase(vaseinfo.row, vaseinfo.column, vaseinfo.content, vaseinfo.skin, vaseinfo.zombie, vaseinfo.plant, vaseinfo.sun);
}

byte __asm__CreateRake[26]
{
	CREATERAKE,
	ADD_ESP(8),
	RET,
};

void Creater::CreateRake(byte row, byte column)
{
	__asm__CreateRake[1] = row;
	__asm__CreateRake[3] = column;
	SETARG(__asm__CreateRake, 5) = PVZBASEADDRESS;
	PVZ::Memory::WriteMemory<unsigned short>(0x40B9E3, 0xA681);
	PVZ::Memory::WriteMemory<byte>(0x40BB2B, 0);
	PVZ::Memory::WriteMemory<int>(0x40BB3B, 0x900C4D8B);
	PVZ::Memory::WriteMemory<int>(0x40BB41, 0x9010458B);
	PVZ::Memory::Execute(STRING(__asm__CreateRake));
	PVZ::Memory::WriteMemory<short>(0x40B9E3, 0x7984);
	PVZ::Memory::WriteMemory<byte>(0x40BB2B, -1);
	PVZ::Memory::WriteMemory<int>(0x40BB3B, 0x10244C8B);
	PVZ::Memory::WriteMemory<int>(0x40BB41, 0x1424448B);
}

byte __asm__CreateCaption[70]
{
	PUSHDWORD(0),
	LEA_ECX_ESP_ADD(0x30),
	UNKNOWSTRINGFUNCTION,
	MOV_ESI(0),
	MOV_ECX(6),
	LEA_EDX_ESP_ADD(0x2C),
	CREATECAPTION,
	MOV_PTR_ESI_ADD(0x88,0),
	MOV_PTR_ESI_ADD(0x8C,0),
	RET,
};

void Creater::CreateCaption(const char* str, int length, CaptionStyle::CaptionStyle style, int duration)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, str, length);
	SETARG(__asm__CreateCaption, 1) = PVZ::Memory::Variable + 100;
	SETARG(__asm__CreateCaption, 23) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x140);
	SETARG(__asm__CreateCaption, 55) = duration;
	SETARG(__asm__CreateCaption, 65) = style;
	PVZ::Memory::Execute(STRING(__asm__CreateCaption));
}

byte __asm__CreateImageCaption[50]
{
	MOV_EDI(0),
	PUSHDWORD(0),
	LEA_ECX_ESP_ADD(0x10),
	UNKNOWSTRINGFUNCTION,
	MOV_ECX(0xF),
	LEA_EDX_ESP_ADD(0xC),
	CREATEIMAGECAPTION,
	RET,
};

void Creater::CreateImageCaption(const char* str, int length)
{
	PVZ::Memory::WriteArray<const char>(PVZ::Memory::Variable + 100, str, length);
	SETARG(__asm__CreateImageCaption, 1) = PVZBASEADDRESS;
	SETARG(__asm__CreateImageCaption, 6) = PVZ::Memory::Variable + 100;
	PVZ::Memory::Execute(STRING(__asm__CreateImageCaption));
}

byte __asm__CreatePlantEffect[19]
{
	CREATEPLANTEFFECT,
	RET,
};

void Creater::CreatePlantEffect(PlantEffectType::PlantEffectType type, int x, int y)
{
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 100, PVZ_BASE);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 104, PVZBASEADDRESS);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 100 + 0x24, type);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 108, x + 50);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 100 + 0xC, y + 50);
	xytorc(&x,&y);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 100 + 0x1C, x);
	PVZ::Memory::WriteMemory<int>(PVZ::Memory::Variable + 100 + 0x28, y);
	SETARG(__asm__CreatePlantEffect, 1) = PVZ::Memory::Variable + 100;
	PVZ::Memory::Execute(STRING(__asm__CreatePlantEffect));
}

byte __asm__CreateExplosion[42]
{
	CREATEEXPLOTION,
	RET,
};

void Creater::CreateExplosion(int x, int y, int radius, BOOLEAN cinder, byte bound, BOOLEAN fromjackzombie)
{
	byte damage = fromjackzombie ? 0xFF : 0x7F;
	__asm__CreateExplosion[1] = damage;
	__asm__CreateExplosion[3] = cinder;
	__asm__CreateExplosion[5] = bound;
	SETARG(__asm__CreateExplosion, 7) = radius;
	SETARG(__asm__CreateExplosion, 12) = y;
	SETARG(__asm__CreateExplosion, 17) = x;
	xytorc(&x, &y);
	__asm__CreateExplosion[22] = x;
	SETARG(__asm__CreateExplosion, 24) = PVZBASEADDRESS;
	PVZ::Memory::Execute(STRING(__asm__CreateExplosion));
}

byte __asm___CreateEffect[39]
{
	MOV_ESI(0),
	_CREATEEFFECT,
	RET,
};

void Creater::CreateEffect(int effectid, float x, float y)
{
	SETARG(__asm___CreateEffect, 1) = PVZ::Memory::ReadPointer(0x6A9EC0, 0x820, 0);
	SETARG(__asm___CreateEffect, 6) = effectid;
	SETARGFLOAT(__asm___CreateEffect, 16) = y;
	SETARGFLOAT(__asm___CreateEffect, 21) = x;
	PVZ::Memory::Execute(STRING(__asm___CreateEffect));
}

byte __asm__CreateSound[26]
{
	MOV_EAX(0),
	MOV_ECX(0),
	CREATESOUND,
	RET,
};

void Creater::CreateSound(int soundid)
{
	SETARG(__asm__CreateSound, 1) = soundid;
	SETARG(__asm__CreateSound, 6) = PVZ::Memory::ReadPointer(0x6A9EC0, 0x784);
	PVZ::Memory::Execute(STRING(__asm__CreateSound));
}

byte __asm__FrozeAll[19]
{
	MOV_EDI(0),
	FORZEALL,
	RET,
};

void Creater::FrozeAll()
{
	SETARG(__asm__FrozeAll, 1) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0xAC);
	PVZ::Memory::Execute(STRING(__asm__FrozeAll));
}

byte __asm__StopSound[24]
{
	MOV_EDI(0),
	MOV_EAX(0),
	STOPSOUND,
	RET,
};

void Creater::StopSound(int soundid)
{
	SETARG(__asm__StopSound, 1) = PVZ::Memory::ReadPointer(0x6A9EC0, 0x784);
	SETARG(__asm__StopSound, 6) = soundid;
	PVZ::Memory::Execute(STRING(__asm__StopSound));
}

byte __asm__CreateIZombieFormation[19]
{
	CREATEIZOMBIEFORMATION,
	RET,
};

void Creater::CreateIZombieFormation(PVZLevel::PVZLevel izlevel)
{
	if (izlevel >= PVZLevel::I_Zombie && izlevel <= PVZLevel::I_Zombie_Endless)
	{
		PVZLevel::PVZLevel curlevel = PVZ::Memory::ReadMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8);
		PVZ::Memory::WriteMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8, izlevel);
		SETARG(__asm__CreateIZombieFormation, 1) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x160);
		PVZ::Memory::Execute(STRING(__asm__CreateIZombieFormation));
		PVZ::Memory::WriteMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8, curlevel);
	}
}

byte __asm__CreateVaseFormation[19]
{
	MOV_ESI(0),
	CREATEVASEFORMATION,
	RET,
};

void Creater::CreateVaseFormation(PVZLevel::PVZLevel vblevel)
{
	if (vblevel >= PVZLevel::Vasebreaker && vblevel <= PVZLevel::Vasebreaker_Endless)
	{
		PVZLevel::PVZLevel curlevel = PVZ::Memory::ReadMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8);
		PVZ::Memory::WriteMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8, vblevel);
		SETARG(__asm__CreateVaseFormation, 1) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x160);
		PVZ::Memory::Execute(STRING(__asm__CreateVaseFormation));
		PVZ::Memory::WriteMemory<PVZLevel::PVZLevel>(PVZ_BASE + 0x7F8, curlevel);
	}
}

byte __asm__CreatePortal[19]
{
	MOV_EDI(0),
	CREATEPORTAL,
	RET,
};

void Creater::__CreatePortal(PVZ* pvz)
{
	PVZ::Griditem* griditems[100];
	int len = pvz->GetAllGriditems(griditems);
	for (int i = 0; i < len; i++)
		if (griditems[i]->Type == GriditemType::PortalBlue || griditems[i]->Type == GriditemType::PortalYellow)
			griditems[i]->NotExist = true;
	SETARG(__asm__CreatePortal, 1) = PVZ::Memory::ReadMemory<int>(PVZBASEADDRESS + 0x160);
	PVZ::Memory::Execute(STRING(__asm__CreatePortal));
}

void Creater::CreatePortal(PVZ* pvz,int yellow1Row, int yellow1Column, int yellow2Row, int yellow2Column, int blue1Row, int blue1Column, int blue2Row, int blue2Column)
{
	PVZ::Memory::WriteMemory<int>(0x426FE9, yellow1Row);
	PVZ::Memory::WriteMemory<int>(0x426FE2, yellow1Column);
	PVZ::Memory::WriteMemory<int>(0x427014, yellow2Row);
	PVZ::Memory::WriteMemory<int>(0x42700D, yellow2Column);
	PVZ::Memory::WriteMemory<int>(0x427044, blue1Row);
	PVZ::Memory::WriteMemory<int>(0x42703D, blue1Column);
	PVZ::Memory::WriteMemory<int>(0x42706D, blue2Row);
	PVZ::Memory::WriteMemory<int>(0x427068, blue2Column);
	__CreatePortal(pvz);
	PVZ::Memory::WriteMemory<int>(0x426FE9, 0);
	PVZ::Memory::WriteMemory<int>(0x426FE2, 2);
	PVZ::Memory::WriteMemory<int>(0x427014, 1);
	PVZ::Memory::WriteMemory<int>(0x42700D, 9);
	PVZ::Memory::WriteMemory<int>(0x427044, 3);
	PVZ::Memory::WriteMemory<int>(0x42703D, 9);
	PVZ::Memory::WriteMemory<int>(0x42706D, 4);
	PVZ::Memory::WriteMemory<int>(0x427068, 2);
}

byte __asm__ClearZombiePreview[19]
{
	MOV_EBX(0),
	CLEARZOMBIEPREVIEW,
	RET,
};

void Creater::__ClearZombiePreview()
{
	SETARG(__asm__ClearZombiePreview, 1) = PVZBASEADDRESS;
	PVZ::Memory::Execute(STRING(__asm__ClearZombiePreview));
}

byte __asm__CreateZombieInLevel[19]
{
	MOV_EDI(0),
	CREATEZOMBIEINLEVEL,
	RET,
};

void Creater::CreateZombieInLevel(ZombieType::ZombieType* ztypes, int length, int wave)
{
	if (wave)
	{
		PVZ::Memory::WriteMemory<int>(0x4092FD, wave);
		PVZ::Memory::WriteMemory<int>(0x4093F2, wave);
		PVZ::Memory::WriteMemory<int>(0x409466, wave);
		PVZ::Memory::WriteMemory<int>(0x409472, wave);
		PVZ::Memory::WriteMemory<int>(0x40947C, wave);
		PVZ::Memory::WriteMemory<int>(0x40948A, wave);
		PVZ::Memory::WriteMemory<int>(0x409499, wave);
	}
	__ClearZombiePreview();
	SETARG(__asm__CreateZombieInLevel, 1) = PVZBASEADDRESS;
	for (int i = 0; i < 33; i++)
		PVZ::Memory::WriteMemory<byte>(PVZBASEADDRESS + 0x54D4 + i, 0);
	for (int i = 0; i < length; i++)
		PVZ::Memory::WriteMemory<byte>(PVZBASEADDRESS + 0x54D4 + ztypes[i], 1);
	PVZ::Memory::Execute(STRING(__asm__CreateZombieInLevel));
	PVZ::Memory::WriteMemory<int>(0x4092FD, 20);
	PVZ::Memory::WriteMemory<int>(0x4093F2, 12);
	PVZ::Memory::WriteMemory<int>(0x409466, 40);
	PVZ::Memory::WriteMemory<int>(0x409472, 30);
	PVZ::Memory::WriteMemory<int>(0x40947C, 0);
	PVZ::Memory::WriteMemory<int>(0x40948A, 10);
	PVZ::Memory::WriteMemory<int>(0x409499, 10);
}


