#pragma once
#include "Enums.h"
#include "MainFuntions.h"

#pragma region definitions

#define STRING(str) str,sizeof(str)/sizeof(*str)
#define SETARG(asmfunction,index) *(int*)(asmfunction+index)

#define PAGE_SIZE 1024
#define PVZ_BASE Memory::ReadMemory<int>(0x6A9EC0)

#define PROPERTY(type,getmethod,setmethod) type getmethod();void setmethod(type value);__declspec(property(get=getmethod,put=setmethod)) type
#define READONLY_PROPERTY(type,getmethod) type getmethod();__declspec(property(get=getmethod)) type
#define WRITEONLY_PROPERTY(type,setmethod) void setmethod(type value);__declspec(property(put=setmethod)) type

#define PROPERTY_BINDING(type,getmethod,getter,setmethod,setter) inline type getmethod(){return getter;};inline void setmethod(type value){setter;};__declspec(property(get=getmethod,put=setmethod)) type
#define READONLY_PROPERTY_BINDING(type,getmethod,getter) inline type getmethod(){return getter;};__declspec(property(get=getmethod)) type
#define WRITEONLY_PROPERTY_BINDING(type,setmethod,setter) inline void setmethod(type value){setter;};__declspec(property(put=setmethod)) type


#define INT_PROPERTY(propname,getmethod,setmethod,offset) PROPERTY_BINDING(int,getmethod,Memory::ReadMemory<int>(BaseAddress+offset),setmethod,Memory::WriteMemory<int>(BaseAddress+offset,value)) propname
#define INT_READONLY_PROPERTY(propname,getmethod,offset) READONLY_PROPERTY_BINDING(int,getmethod,Memory::ReadMemory<int>(BaseAddress+offset)) propname
#define T_PROPERTY(type,propname,getmethod,setmethod,offset) PROPERTY_BINDING(type,getmethod,Memory::ReadMemory<type>(BaseAddress+offset),setmethod,Memory::WriteMemory<type>(BaseAddress+offset,value)) propname
#define T_READONLY_PROPERTY(type,propname,getmethod,offset) READONLY_PROPERTY_BINDING(type,getmethod,Memory::ReadMemory<type>(BaseAddress+offset)) propname

#pragma endregion

/*Only version 1.0.0.1051 is fully supported*/
class PVZ
{
public:
	PVZ(DWORD pid);
	~PVZ();

#pragma region Memory Class

	class Memory
	{
	public:
		static int Variable;
		static HANDLE hProcess;
		static DWORD processId;
		static HWND mainwindowhandle;
		template <class T>
		inline static T ReadMemory(int address)
		{
			T buffer = (T)NULL;
			ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
			return buffer;
		};
		template <class T>
		inline static BOOL WriteMemory(int address, T value)
		{
			return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), NULL);
		};
		template <class T>
		inline static BOOL ReadArray(int address, T* result, size_t length)
		{
			return ReadProcessMemory(hProcess, (LPCVOID)address, (LPVOID)result, length, NULL);
		};
		template <class T>
		inline static BOOL WriteArray(int address, T* result, size_t length)
		{
			return WriteProcessMemory(hProcess, (LPVOID)address, result, length, NULL);
		};
		static int ReadPointer(int baseaddress, int offset);
		static int ReadPointer(int baseaddress, int offset, int offset1);
		static int ReadPointer(int baseaddress, int offset, int offset1, int offset2);
		static BOOL AllAccess(int address);
		static int AllocMemory();
		static void CreateThread(int address);
		static void FreeMemory(int address);
		static int Execute(byte asmcode[], int lengrh);
		static void InjectDll(LPCSTR dllname);
	};

#pragma endregion

#pragma region properties

	READONLY_PROPERTY(const char*, __get_Version) Version;
	READONLY_PROPERTY(PVZVersion, __get_GameVersion) GameVersion;
	PROPERTY(double, __get_MusicVolume, __set_MusicVolume) MusicVolume;//range[0,1]
	PROPERTY(double, __get_SoundFXVolume, __set_SoundFXVolume) SoundFXVolume;//range[0,1]
	INT_READONLY_PROPERTY(ZombiesCount, __get_ZombiesCount, 0xA0);
	INT_READONLY_PROPERTY(PlantsCount, __get_PlantsCount, 0xBC);
	INT_READONLY_PROPERTY(ProjectilesCount, __get_ProjectilesCount, 0xD8);
	INT_READONLY_PROPERTY(CoinsCount, __get_CoinsCount, 0xF4);
	INT_READONLY_PROPERTY(LawnmoversCount, __get_LawnmoversCount, 0x110);
	INT_READONLY_PROPERTY(GriditemsCount, __get_GriditemsCount, 0x12C);
	PROPERTY_BINDING(
		PVZLevel,
		__get_LevelId,
		Memory::ReadMemory<PVZLevel>(PVZ_BASE + 0x7F8),
		__set_LevelId,
		Memory::WriteMemory<PVZLevel>(PVZ_BASE + 0x7F8, value)) LevelId;
	PROPERTY_BINDING(
		PVZGameState,
		__get_GameState,
		Memory::ReadMemory<PVZGameState>(PVZ_BASE + 0x7FC),
		__set_GameState,
		Memory::WriteMemory<PVZGameState>(PVZ_BASE + 0x7FC, value)) GameState;
	PROPERTY_BINDING(
		BOOLEAN,
		__get_FreePlantingCheat,
		Memory::ReadMemory<BOOLEAN>(PVZ_BASE + 0x814),
		__set_FreePlantingCheat,
		Memory::WriteMemory<BOOLEAN>(PVZ_BASE + 0x814, value)) FreePlantingCheat;
	PROPERTY_BINDING(
		BOOLEAN,
		__get_FullVersion,
		Memory::ReadMemory<BOOLEAN>(PVZ_BASE + 0x8C0),
		__set_FullVersion,
		Memory::WriteMemory<BOOLEAN>(PVZ_BASE + 0x8C0, value)) FullVersion;
	READONLY_PROPERTY_BINDING(
		int,
		__get_BaseAddress,
		Memory::ReadMemory<int>(PVZ_BASE + 0x768)) BaseAddress;
	INT_PROPERTY(ViewX, __get_ViewX, __set_ViewX, 0x30);
	INT_PROPERTY(ViewY, __get_ViewY, __set_ViewY, 0x34);
	INT_PROPERTY(ViewLength, __get_ViewLength, __set_ViewLength, 0x38);
	INT_PROPERTY(ViewHeight, __get_ViewHeight, __set_ViewHeight, 0x3C);
	T_PROPERTY(BOOLEAN, GamePaused, __get_GamePaused, __set_GamePaused, 0x164);
	INT_PROPERTY(SunDropCountdown, __get_SunDropCountdown, __set_SunDropCountdown, 0x5538);
	INT_PROPERTY(SunDropCount, __get_SunDropCount, __set_SunDropCount, 0x553C);
	PROPERTY(SceneType, __get_LevelScene, __set_LevelScene) LevelScene;
	READONLY_PROPERTY_BINDING(
		BOOLEAN,
		__get_SixRoute,
		(LevelScene == Pool_Scene) || (LevelScene == Fog)) SixRoute;
	INT_PROPERTY(AdventureLevel, __get_AdventureLevel, __set_AdventureLevel, 0x5550);
	INT_PROPERTY(Sun, __get_Sun, __set_Sun, 0x5560);
	PROPERTY(int, __get_WaveCount, __set_WaveCount) WaveCount;
	/*exclude preparing time*/
	INT_READONLY_PROPERTY(PlayingTime, __get_PlayingTime, 0x5568);
	/*include preparing time*/
	INT_READONLY_PROPERTY(PlayingTime2, __get_PlayingTime2, 0x556C);
	/*lose focus and recount*/
	INT_READONLY_PROPERTY(PlayingTime3, __get_PlayingTime3, 0x5570);
	INT_READONLY_PROPERTY(CurrentWave, __get_CurrentWave, 0x557C);
	INT_READONLY_PROPERTY(RefreshedWave, __get_RefreshedWave, 0x5580);
	INT_PROPERTY(FlashTip, __get_FlashTip, __set_FlashTip, 0x5584);
	/*Flash tips for novice tutorials*/
	INT_PROPERTY(RefreshHp, __get_RefreshHp, __set_RefreshHp, 0x5594);
	INT_READONLY_PROPERTY(CurrentWaveHp, __get_CurrentWaveHp, 0x5598);
	INT_PROPERTY(NextWaveCountdown, __get_NextWaveCountdown, __set_NextWaveCountdown, 0x559C);
	INT_READONLY_PROPERTY(NextWaveCountdownInitialValue, __get_NextWaveCountdownInitialValue, 0x55A0);
	INT_PROPERTY(HugeWaveCountdown, __get_HugeWaveCountdown, __set_HugeWaveCountdown, 0x55A4);
	T_PROPERTY(BOOLEAN, HaveShovel, __get_HaveShovel, __set_HaveShovel, 0x55F1);
	T_PROPERTY(DebugModeType, DebugMode, __get_DebugMode, __set_DebugMode, 0x55F8);

#pragma region keyboard code

	T_PROPERTY(BOOLEAN, Mustache, __get_Mustache, __set_Mustache, 0x5761);
	T_PROPERTY(BOOLEAN, Trickedout, __get_Trickedout, __set_Trickedout, 0x5762);
	T_PROPERTY(BOOLEAN, Future, __get_Future, __set_Future, 0x5763);
	T_PROPERTY(BOOLEAN, Pinata, __get_Pinata, __set_Pinata, 0x5764);
	T_PROPERTY(BOOLEAN, Dance, __get_Dance, __set_Dance, 0x5765);
	T_PROPERTY(BOOLEAN, Daisies, __get_Daisies, __set_Daisies, 0x5766);
	T_PROPERTY(BOOLEAN, Sukhbir, __get_Sukhbir, __set_Sukhbir, 0x5767);

#pragma endregion

	INT_READONLY_PROPERTY(EatenPlants, __get_EatenPlants, 0x5798);
	INT_READONLY_PROPERTY(ShoveledPlants, __get_ShoveledPlants, 0x579C);

#pragma endregion

#pragma region classes

	class Animation
	{
		int BaseAddress;
	public:
		Animation(int idoraddress);
	};
	class Lawn
	{
		int BaseAddress;
	public:
		Lawn(int baseaddress);
		LawnType GetGridType(int column, int row);
		void SetGridType(int column, int row, LawnType type);
		RouteType GetRouteType(int route);
		void SetRouteType(int route, RouteType type);
	};
	class Icetrace
	{
		int BaseAddress;
	public:
		Icetrace(int baseaddress);
		int GetX(int route);
		void SetX(int route, int x);
		int GetDisappearCountdown(int route);
		void SetDisappearCountdown(int route, int cs);
	};
	class Wave
	{
		int BaseAddress;
	public:
		Wave(int baseaddress);
		READONLY_PROPERTY(int, __get_Count) Count;
		void GetAll(ZombieType* ztypes);
		void SetAll(ZombieType* ztypes, size_t length);
		ZombieType Get(int index);
		void Set(int index, ZombieType ztype);
		void Del(int index);
		void Add(ZombieType ztype);
	};
	class Mouse
	{
		int BaseAddress;
	public:
		Mouse(int baseaddress);
		T_READONLY_PROPERTY(BOOLEAN, InGameArea, __get_InGameArea, 0xDC);
		INT_READONLY_PROPERTY(X, __get_X, 0xE0);
		INT_READONLY_PROPERTY(Y, __get_Y, 0xE4);
		T_READONLY_PROPERTY(MouseClickState, ClickState, __get_ClickState, 0xE8);
		void WMClick(short x, short y);
	};
	class Zombie
	{
		int BaseAddress;
#if _DEBUG
		ZombieType DebugType;
#endif
	public:
		Zombie(int indexoraddress);
		INT_PROPERTY(ImageX, __get_ImageX, __set_ImageX, 8);
		INT_PROPERTY(ImageY, __get_ImageY, __set_ImageY, 0xC);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x1C);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x20);
		T_PROPERTY(ZombieType, Type, __get_Type, __set_Type, 0x24);
		INT_PROPERTY(State, __get_State, __set_State, 0x28);
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x2C);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x30);
		void Light(int cs = 100);
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x68);
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x74);
		struct CollisionBox
		{
			int X;
			int Y;
			int Length;
			int Height;
		};
		void GetCollision(CollisionBox* collbox);
		void SetCollision(CollisionBox* collbox);
		void GetAttackCollision(CollisionBox* collbox);
		void SetAttackCollision(CollisionBox* collbox);
		INT_PROPERTY(DecelerateCountdown, __get_DecelerateCountdown, __set_DecelerateCountdown, 0xAC);
		INT_PROPERTY(FixedCountdown, __get_FixedCountdown, __set_FixedCountdown, 0xB0);
		INT_PROPERTY(FrozenCountdown, __get_FrozenCountdown, __set_FrozenCountdown, 0xB4);
		T_PROPERTY(BOOLEAN, Hypnotized, __get_Hypnotized, __set_Hypnotized, 0xB8);
		T_PROPERTY(BOOLEAN, Blowaway, __get_Blowaway, __set_Blowaway, 0xB9);
		T_PROPERTY(BOOLEAN, Dying, __get_Dying, __set_Dying, 0xBA);
		T_READONLY_PROPERTY(BOOLEAN, HandBroken, __get_HandBroken, 0xBB);
		T_PROPERTY(BOOLEAN, SthinHandOrYetiLeft, __get_SthinHandOrYetiLeft, __set_SthinHandOrYetiLeft, 0xBC);
		T_PROPERTY(BOOLEAN, InWater, __get_InWater, __set_InWater, 0xBD);
		T_PROPERTY(BOOLEAN, GarlicBited, __get_GarlicBited, __set_GarlicBited, 0xBF);
		struct AccessoriesType1
		{
			ZombieAccessoriesType1 Type;
			int Hp;
			int MaxHp;
		};
		struct AccessoriesType2
		{
			ZombieAccessoriesType2 Type;
			int Hp;
			int MaxHp;
		};
		void GetAccessoriesType1(AccessoriesType1* acctype1);
		void SetAccessoriesType1(AccessoriesType1* acctype1);
		void GetAccessoriesType2(AccessoriesType2* acctype2);
		void SetAccessoriesType2(AccessoriesType2* acctype2);
		void GetBodyHp(int* hp, int* maxhp);
		void SetBodyHp(int hp, int maxhp);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0xEC);
		void GetAnimation(PVZ::Animation* animation);
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x11C);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x158);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Hit(int damge, DamageType type = Direct);
		void Blast();
		void Butter();
	};
	class Projectile
	{
		int BaseAddress;
#if _DEBUG
		ProjectileType DebugType;
#endif
	public:
		Projectile(int indexoraddress);
		INT_PROPERTY(ImageX, __get_ImageX, __set_ImageX, 8);
		INT_PROPERTY(ImageY, __get_ImageY, __set_ImageY, 0xC);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x1C);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x20);
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x30);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x34);
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x38);
		T_PROPERTY(FLOAT, XSpeed, __get_XSpeed, __set_XSpeed, 0x3C);
		T_PROPERTY(FLOAT, YSpeed, __get_YSpeed, __set_YSpeed, 0x40);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x50);
		T_PROPERTY(MotionType, Motion, __get_Motion, __set_Motion, 0x58);
		T_PROPERTY(ProjectileType, Type, __get_Type, __set_Type, 0x5C);
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		T_PROPERTY(FLOAT, RotationAngle, __get_RotationAngle, __set_RotationAngle, 0x68);
		T_PROPERTY(FLOAT, RotationSpeed, __get_RotationSpeed, __set_RotationSpeed, 0x6C);
		INT_PROPERTY(DamageAbility, __get_DamageAbility, __set_DamageAbility, 0x74);
		INT_PROPERTY(TracktargetId, __get_TracktargetId, __set_TracktargetId, 0x88);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x90);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void OnFire();
	};
	class Plant
	{
		int BaseAddress;
#if _DEBUG
		PlantType DebugType;
#endif
	public:
		Plant(int indexoraddress);
		INT_PROPERTY(X, __get_X, __set_X, 8);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xC);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x1C);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x20);
		T_PROPERTY(PlantType, Type, __get_Type, __set_Type, 0x24);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x28);
		INT_PROPERTY(State, __get_State, __set_State, 0x3C);
		INT_PROPERTY(Hp, __get_Hp, __set_Hp, 0x40);
		INT_PROPERTY(MaxHp, __get_MaxHp, __set_MaxHp, 0x44);
		T_PROPERTY(BOOLEAN, Aggressive, __get_Aggressive, __set_Aggressive, 0x48);
		INT_PROPERTY(BloverDisappearCountdown, __get_BloverDisappearCountdown, __set_BloverDisappearCountdown, 0x4C);
		INT_PROPERTY(EffectiveCountdown, __get_EffectiveCountdown, __set_EffectiveCountdown, 0x50);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x54);
		INT_PROPERTY(ShootOrProductCountdown, __get_ShootOrProductCountdown, __set_ShootOrProductCountdown, 0x58);
		INT_PROPERTY(ShootOrProductInterval, __get_ShootOrProductInterval, __set_ShootOrProductInterval, 0x5C);
		INT_PROPERTY(ShootingCountdown, __get_ShootingCountdown, __set_ShootingCountdown, 0x90);
		void GetAnimationPart1(PVZ::Animation* animation);
		void GetAnimationPart2(PVZ::Animation* animation);
		void Light(int cs = 100);
		void Flash(int cs = 100);
		T_PROPERTY(FLOAT, ImageXOffset, __get_ImageXOffset, __set_ImageXOffset, 0xC0);
		T_PROPERTY(FLOAT, ImageYOffset, __get_ImageYOffset, __set_ImageYOffset, 0xC4);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x141);
		T_PROPERTY(BOOLEAN, Squash, __get_Squash, __set_Squash, 0x142);
		T_PROPERTY(BOOLEAN, Sleeping, __get_Sleeping, __set_Sleeping, 0x143);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x148);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void CreateEffect();
		void SetStatic();
		void Shoot(PVZ::Projectile* pro, int targetid = -1);
	};
	

#pragma endregion

#pragma region methods

	Lawn* GetLawn();
	Icetrace* GetIcetrace();
	Wave* GetWave(int index);
	void GetZombieSeed(ZombieType* ztypes);
	void Earthquake(int horizontalAmplitude = 2, int verticalAmplitude = 4, int duration = 20);
	void Assault(int countdown = 1);
	void Win();
	void Bell(int countdown = 1);
	int GetAllZombies(Zombie* zombies[]);
	int GetAllPlants(Plant* plants[]);

#pragma endregion

};
