#pragma once
#include "PVZ.h"

namespace Creator
{

inline short makeshort(byte b1, byte b2)
{
	return (b2 << 8) + b1;
}
inline void xytorc(int* x, int* y)
{
	int temp = *y;
	*y = (*x - 40) / 80;
	SceneType::SceneType scene = PVZ::Memory::ReadMemory<SceneType::SceneType>(PVZBASEADDRESS + 0x554C);
	bool sixroute = (scene == SceneType::Pool) || (scene == SceneType::Fog);
	*x = sixroute ? (temp - 80) / 85 : (temp - 80) / 100;
}


#define PI 3.1415926f
#define CREATEREANIMATION INVOKE_DWORD_DWORD_DWORD(0x453C30,0,0,0)
#define CREATEZOMBIE INVOKE_BYTE_BYTE(0x42A0F0,0,0)
#define CREATEPLANT INVOKE_DWORD_BYTE_BYTE_BYTE(0x40D120,0,0,0,-1)
#define CREATEPROJECTILE INVOKE_DWORD_DWORD_BYTE_BYTE_BYTE(0x40D620,0,0,0,0,0)
#define CREATECOIN INVOKE_DWORD_DWORD_BYTE_BYTE(0x40CB10,0,0,0,0)
#define RESETLAWNMOVER INVOKE_DWORD(0x40BC70,0)
#define CREATEGRDITEM INVOKE(0x41E1C0)
#define CREATEGRAVE INVOKE(0x426620)
#define CREATECRATER INVOKE_BYTE(0x408F80,0)
#define CREATELADDER INVOKE_BYTE(0x408F40,0)
#define CREATERAKE INVOKE_DWORD_BYTE_BYTE(0x40B9C0,0,0,0)
#define CHARSTRTOSTRING INVOKE(0x404450)
#define CREATECAPTION INVOKE(0x459010)
#define CREATEIMAGECAPTION INVOKE(0x40CA10)
#define CREATEPLANTEFFECT INVOKE_DWORD(0x4666A0,0)
#define CREATEEXPLOTION INVOKE_DWORD_BYTE_DWORD_DWORD_DWORD_BYTE_BYTE_BYTE(0x41D8A0,0,0,0,0,0,0,0,0)
#define _CREATEEFFECT INVOKE_DWORD_DWORD_DWORD_DWORD(0x518A70,0,0,0x61A80,0)
#define CREATESOUND INVOKE_BYTE(0x515020,0)
#define CREATEUPPERSOUND INVOKE_DWORD(0x4560C0,0)
#define FREEZEALL INVOKE(0x466420)
#define STOPSOUND INVOKE(0x515290)
#define CREATEIZOMBIEFORMATION INVOKE_DWORD(0x42A890,0)
#define CREATEVASEFORMATION INVOKE(0x4286F0)
#define CREATEPORTAL INVOKE(0x426FC0)
#define CLEARZOMBIEPREVIEW INVOKE(0x40DF70)
#define CREATEZOMBIEINLEVEL INVOKE(0x4092E0)

	SPT<PVZ::Animation> CreateReanimation(AnimationType::AnimationType type, float x, float y, int layer = 0x310000);

	//在指定位置生成一个指定类型的僵尸。
	//僵王博士将会被强制生成在 0 行 0 列。
	SPT<PVZ::Zombie> CreateZombie(ZombieType::ZombieType type, int row, byte column);

	SPT<PVZ::Plant> CreatePlant(PlantType::PlantType type, int row, byte column, BOOLEAN imitative = false);

	SPT<PVZ::Projectile> CreateProjectile(ProjectileType::ProjectileType type, byte row, int x);

	void AsmInit();

	//如果调用过 AsmInit()，程序结束之前一定要调用此函数
	void AsmReset();

	//你需要先调用一次AsmInit后才能使用这个函数
	SPT<PVZ::Projectile> CreateProjectile(ProjectileType::ProjectileType type, int x, int y, float angle, float speed);

	SPT<PVZ::Coin> CreateCoin(CoinType::CoinType type,int x,int y,CoinMotionType::CoinMotionType motion);

	void ResetLawnmover();

	//just a Bottom implementation
	SPT<PVZ::Griditem> CreateGriditem();

	void CreateGrave(int row, int column);

	SPT<PVZ::Crater> CreateCrater(int row, int column,int duration);

	SPT<PVZ::Griditem> CreateLadder(int row, byte column);

	SPT<PVZ::Vase> CreateVase(int row, int column, VaseContent::VaseContent content, VaseSkin::VaseSkin skin = VaseSkin::VaseSkinUnknow, ZombieType::ZombieType zombie = ZombieType::Zombie, PlantType::PlantType plant = PlantType::Peashooter, int sun = 0);

	SPT<PVZ::Portal> CreatePortal(int row, int column, int isYellow = 0);
	
	struct VaseCreateInfo
	{
		int row;
		int column;
		VaseContent::VaseContent content;
		VaseSkin::VaseSkin skin;
		ZombieType::ZombieType zombie;
		PlantType::PlantType plant;
		int sun;
	};

	SPT<PVZ::Vase> CreateVase(VaseCreateInfo vaseinfo);

	void CreateRake(byte row, byte column);

	void CreateCaption(const char* str, int length, CaptionStyle::CaptionStyle style, int duration = 500);

	void CreateImageCaption(const char* str, int length);

	void CreatePlantEffect(PlantEffectType::PlantEffectType type, int x, int y);

	void CreateExplosion(int x, int y, int radius, BOOLEAN cinder = true, byte bound = 5, BOOLEAN fromjackzombie = false);

	void CreateEffect(EffectType::EffectType type, float x, float y);

	//部分音效是持续的，需要用StopSound手动停止音效持续播放
	void CreateSound(int soundid);

	void CreateLowerSound(LowerSoundType::LowerSoundType sound);

	void CreateUpperSound(UpperSoundType::UpperSoundType sound);

	//当前关卡必须至少存在过一个植物，此函数才有效
	void FrozeAll();

	void StopSound(int soundid);

	void CreateIZombieFormation(PVZLevel::PVZLevel izlevel);

	void CreateVaseFormation(PVZLevel::PVZLevel vblevel);

	//你需要先调用一次AsmInit后才能使用这个函数
	void __CreatePortal();

	//你需要先调用一次AsmInit后才能使用这个函数
	void CreatePortal(int yellow1Row, int yellow1Column, int yellow2Row, int yellow2Column, int blue1Row, int blue1Column, int blue2Row, int blue2Column);

	void __ClearZombiePreview();

	//生成出怪列表
	//wave = 0 means defalt and Non-intervention
	void CreateZombieInLevel(ZombieType::ZombieType* ztypes, int length, int wave = 0);

}