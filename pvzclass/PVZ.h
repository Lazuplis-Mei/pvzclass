#pragma once
#include "Enums.h"
#include "Flags.h"
#include "AsmFunctions.h"
#include <ctime>
#include <memory>
#include <vector>

#pragma region definitions

#define STRING(str) str,sizeof(str)/sizeof(*str)
#define SETARG(asmfunction,index) *(int*)(asmfunction+index)
#define SETARGFLOAT(asmfunction,index) *(float*)(asmfunction+index)

#define PAGE_SIZE 1024
#define PVZ_BASE PVZ::Memory::ReadMemory<int>(0x6A9EC0)
#define PVZBASEADDRESS PVZ::Memory::ReadMemory<int>(PVZ_BASE + 0x768)

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

#define LOGICALINCLUDE(c,v) (c&v)==v

#define SPT std::shared_ptr 
#define UPT std::unique_ptr
#define MKU std::make_unique
#define MKS std::make_shared

#pragma endregion

#define AP_ZOMBIESPEED		1
#define AP_ZOMBIECOLOR		2
#define AP_ZOMBIESCALE		4
#define AP_PLANTCOLOR		8
#define AP_PLANTSCALE		16

#define GPD_RIGHT			0
#define GPD_LEFT			1

#define MINGAM_ENABLE		2
#define MINGAM_DISABLE		-1

#define MINGAME_STARTED		1
#define MINGAME_NOTSTARTED	-1

#define APA_LOOP			1
#define APA_ONCE_DISAPPEAR	2
#define APA_ONCE_STOP		3

#define ID_INDEX(id) ((id) & 0x0000FFFF)
#define ID_RANK(id) ((id) & 0xFFFF0000)

#define HZC_COMMON 1
#define HZC_BALLOON_AIR 2
#define HZC_SNORKED_UNDER 4
#define HZC_NOT_GROUNDED 16
#define HZC_DYING 32
#define HZC_DIGGER_UNDER 64
#define HZC_HYPNOTIZED 128


/*Only version 1.0.0.1051 is fully supported*/
namespace PVZ
{
	void InitPVZ(DWORD pid);
	void QuitPVZ();

#pragma region Memory Class

	class Memory
	{
	public:
		/*	000-100存放创建子弹的函数
			100-200存放字符串或者PlantEffect的伪造植物对象
			300-400存放__autocollect_set
			400-500存放__asm__Plant_memset
			500-600存放Execute的同步代码 */
		static int Variable;
		static HANDLE hProcess;
		static DWORD processId;
		// 主线程（第一个线程），在初始化EventHandler后赋值
		static HANDLE hThread;
		static DWORD mainThreadId;
		static HWND mainwindowhandle;
		// 如果为true，则不会等待PVZ进程，立即执行远程代码
		static bool immediateExecute;
		// 如果为true，则在当前线程执行代码，在dll中设置为true
		static bool localExecute;
		static int DLLAddress;
		template <class T>
		inline static T ReadMemory(int address)
		{
			if (localExecute)
			{
				T* buffer = (T*)address;
				return *buffer;
			}
			else
			{
				T buffer = (T)NULL;
				ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
				return buffer;
			}
		};
		template <class T>
		inline static BOOL WriteMemory(int address, T value)
		{
			if (localExecute)
			{
				AllAccess(address);
				T* buffer = (T*)address;
				*buffer = value;
				return true;
			}
			else
			{
				return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), NULL);
			}
		};
		template <class T>
		inline static BOOL ReadArray(int address, T* result, size_t length)
		{
			if (localExecute)
			{
				memcpy(result, (const void*)address, length);
				return true;
			}
			else
			{
				return ReadProcessMemory(hProcess, (LPCVOID)address, (LPVOID)result, length, NULL);
			}
		};
		template <class T>
		inline static BOOL WriteArray(int address, T* value, size_t length)
		{
			if (localExecute)
			{
				AllAccess(address);
				memcpy((void*)address, value, length);
				return true;
			}
			else
			{
				return WriteProcessMemory(hProcess, (LPVOID)address, value, length, NULL);
			}
		};
		static int ReadPointer(int baseaddress, int offset);
		static int ReadPointer(int baseaddress, int offset, int offset1);
		static int ReadPointer(int baseaddress, int offset, int offset1, int offset2);
		static BOOL AllAccess(int address);
		static int AllocMemory(int pages = 1, int size = 0);
		static void CreateThread(int address);
		static void FreeMemory(int address);
		static int Execute(byte asmcode[], int lengrh);
		static bool InjectDll(const char* dllname);
		static int GetProcAddress(const char* procname);
		static int InvokeDllProc(const char* procname);
		static void WaitPVZ(); // 等待PVZ到达更新前
		static void ResumePVZ(); // 恢复PVZ
	};

#pragma endregion

#pragma region structs

	struct CollisionBox
	{
		int X;
		int Y;
		int Width;
		int Height;
	};

	struct Color
	{
		int Red;
		int Green;
		int Blue;
		int Alpha;
	};

#pragma endregion

#pragma region classes
	class BaseClass
	{
	protected:
		int BaseAddress;
	public:
		BaseClass(int address) : BaseAddress(address){};
		int GetBaseAddress()
		{
			return(this->BaseAddress);
		}
	};

	class PVZutil
	{
	public:
		READONLY_PROPERTY(const char*,				__get_Version)		Version;
		READONLY_PROPERTY(PVZVersion::PVZVersion,	__get_GameVersion)	GameVersion;
	};

	//@brief 游戏程序主类（原 LawnApp）。
	class PVZApp : public BaseClass
	{
	public:
		PVZApp(DWORD address) : BaseClass(address) {};
		PROPERTY(double,						__get_MusicVolume,	__set_MusicVolume)			aMusicVolume;//range[0,1]
		PROPERTY(double,						__get_SoundFXVolume,__set_SoundFXVolume)		SoundFXVolume;//range[0,1]
		T_PROPERTY(DWORD,						PrimaryThreadId,	__get_PrimaryThreadId,		__set_PrimaryThreadId,		0x33C);
		T_PROPERTY(BOOLEAN,						Shutdown,			__get_Shutdown,				__set_Shutdown,				0x341);
		T_PROPERTY(HWND,						HWnd,				__get_HWnd,					__set_HWnd,					0x350);
		T_PROPERTY(PVZLevel::PVZLevel,			LevelId,			__get_LevelId,				__set_LevelId,				0x7F8);
		T_PROPERTY(PVZGameState::PVZGameState,	GameState,			__get_GameState,			__set_GameState,			0x7FC);
		T_PROPERTY(BOOLEAN,						FreePlantingCheat,	__get_FreePlantingCheat,	__set_FreePlantingCheat,	0x814);
		T_PROPERTY(BOOLEAN,						FullVersion,		__get_FullVersion,			__set_FullVersion,			0x8C0);
	};
	SPT<PVZApp> GetPVZApp();

	class Zombie;
	class Plant;
	class Projectile;
	class Coin;
	class Lawnmover;
	class Griditem;
	class MousePointer;
	class Caption;
	class CardSlot;
	class Miscellaneous;
	class Lawn;
	class Icetrace;
	class Wave;
	class Widget
	{
	protected:
		int BaseAddress;
	public:
		Widget(int address) : BaseAddress(address) {};
		int GetBaseAddress();
		INT_PROPERTY(ViewX,			__get_ViewX,		__set_ViewX,		0x30);
		INT_PROPERTY(ViewY,			__get_ViewY,		__set_ViewY,		0x34);
		INT_PROPERTY(ViewLength,	__get_ViewLength,	__set_ViewLength,	0x38);
		INT_PROPERTY(ViewHeight,	__get_ViewHeight,	__set_ViewHeight,	0x3C);
	};
	class Board : public Widget
	{
	public:
		Board(int address) : Widget(address) {};
		SPT<PVZApp> GetPVZApp();
		INT_READONLY_PROPERTY(ZombiesCount, __get_ZombiesCount, 0xA0);
		INT_READONLY_PROPERTY(PlantsCount, __get_PlantsCount, 0xBC);
		INT_READONLY_PROPERTY(ProjectilesCount, __get_ProjectilesCount, 0xD8);
		INT_READONLY_PROPERTY(CoinsCount, __get_CoinsCount, 0xF4);
		INT_READONLY_PROPERTY(LawnmoversCount, __get_LawnmoversCount, 0x110);
		INT_READONLY_PROPERTY(GriditemsCount, __get_GriditemsCount, 0x12C);
		T_PROPERTY(BOOLEAN, GamePaused, __get_GamePaused, __set_GamePaused, 0x164);

#pragma region fog

		int GetGridFog(int row, int column);
		T_PROPERTY(FLOAT, FogOffset, __get_FogOffset, __set_FogOffset, 0x5D0);
		INT_PROPERTY(FogBlownCountDown, __get_FogBlownCountDown, __set_FogBlownCountDown, 0x5D4);

#pragma endregion

		INT_PROPERTY(SunDropCountdown, __get_SunDropCountdown, __set_SunDropCountdown, 0x5538);
		INT_PROPERTY(SunDropCount, __get_SunDropCount, __set_SunDropCount, 0x553C);
		PROPERTY(SceneType::SceneType, __get_LevelScene, __set_LevelScene) LevelScene;
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
		INT_PROPERTY(ShowMoneyCountdown, __get_ShowMoneyCountdown, __set_ShowMoneyCountdown, 0x55F4);
		T_PROPERTY(DebugModeType::DebugModeType, DebugMode, __get_DebugMode, __set_DebugMode, 0x55F8);
		INT_PROPERTY(LevelProcessBar, __get_LevelProcessBar, __set_LevelProcessBar, 0x5610);

		T_PROPERTY(BOOLEAN, Mustache, __get_Mustache, __set_Mustache, 0x5761);
		T_PROPERTY(BOOLEAN, Trickedout, __get_Trickedout, __set_Trickedout, 0x5762);
		T_PROPERTY(BOOLEAN, Future, __get_Future, __set_Future, 0x5763);
		T_PROPERTY(BOOLEAN, Pinata, __get_Pinata, __set_Pinata, 0x5764);
		T_PROPERTY(BOOLEAN, Dance, __get_Dance, __set_Dance, 0x5765);
		T_PROPERTY(BOOLEAN, Daisies, __get_Daisies, __set_Daisies, 0x5766);
		T_PROPERTY(BOOLEAN, Sukhbir, __get_Sukhbir, __set_Sukhbir, 0x5767);

		INT_READONLY_PROPERTY(EatenPlants, __get_EatenPlants, 0x5798);
		INT_READONLY_PROPERTY(ShoveledPlants, __get_ShoveledPlants, 0x579C);

		void GetZombieAllowed(ZombieType::ZombieType* ztypes);

		READONLY_PROPERTY_BINDING(
			BOOLEAN,
			__get_SixRoute,
			(LevelScene == SceneType::Pool) || (LevelScene == SceneType::Fog)) SixRoute;

#pragma region methods

		int GridToXPixel(int row, int column);
		int GridToYPixel(int row, int column);
		void Assault(int countdown = 1);
		void Bell(int countdown = 1);
		void Earthquake(int horizontalAmplitude = 2, int verticalAmplitude = 4, int duration = 20);
		void Lose();
		void Win();
		bool Save(const char* path, int pathlen);
		bool Load(const char* path, int pathlen);

#pragma endregion

#pragma region getmethod
		std::vector<SPT<Zombie>> GetAllZombies();
		std::vector<SPT<Plant>> GetAllPlants();
		std::vector<SPT<Projectile>> GetAllProjectile();
		std::vector<SPT<Coin>> GetAllCoins();
		std::vector<SPT<Lawnmover>> GetAllLawnmovers();
		std::vector<SPT<Griditem>> GetAllGriditems();
		SPT<Lawn> GetLawn();
		SPT<Icetrace> GetIcetrace();
		SPT<Wave> GetWave(int index);
		SPT<MousePointer> GetMousePointer();
		SPT<Caption> GetCaption();
		SPT<CardSlot> GetCardSlot();
		SPT<Miscellaneous> GetMiscellaneous();
#pragma endregion
	};
	class SeedChooserScreen : public Widget
	{
	public:
		SeedChooserScreen(int address) : Widget(address) {};

		class ChosenSeed : public BaseClass
		{
		public:
			ChosenSeed(int address) : BaseClass(address) {};
			INT_PROPERTY(X, __get_X, __set_X, 0);
			INT_PROPERTY(Y, __get_Y, __set_Y, 4);
			T_PROPERTY(CardType::CardType, Type, __get_Type, __set_Type, 0x20);
			T_PROPERTY(SeedState::SeedState, State, __get_State, __set_State, 0x24);
			INT_PROPERTY(IndexInSlot, __get_IndexInSlot, __set_IndexInSlot, 0x28);
			T_PROPERTY(BOOLEAN, Refreshing, __get_Refreshing, __set_Refreshing, 0x2C);
			INT_PROPERTY(RefreshCounter, __get_RefreshCounter, __set_RefreshCounter, 0x30);
			T_PROPERTY(CardType::CardType, ImitaterType, __get_ImitaterType, __set_ImitaterType, 0x34);
			T_PROPERTY(BOOLEAN, CrazyDavePick, __get_CrazyDavePick, __set_CrazyDavePick, 0x38);
		};

		SPT<PVZ::Board> GetBoard();
		SPT<ChosenSeed> GetChosenSeed(int num);
		T_PROPERTY(BOOLEAN, IsViewingLawn, __get_IsViewingLawn, __set_IsViewingLawn, 0x0D38);
	};
	//Do NOT construct this class directly!
	class GameObject : public BaseClass
	{
	public:
		GameObject() : BaseClass(0) {};
		SPT<PVZ::Board> GetBoard()
		{
			return(MKS<PVZ::Board>(Memory::ReadMemory<int>(BaseAddress + 4)));
		}
		INT_PROPERTY(ImageX, __get_ImageX, __set_ImageX, 8);
		INT_PROPERTY(ImageY, __get_ImageY, __set_ImageY, 0xC);
		INT_PROPERTY(Width, __get_Width, __set_Width, 0x10);
		INT_PROPERTY(Height, __get_Height, __set_Height, 0x14);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x1C);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x20);
	};
	class TrackInstance;
	class AttachEffect
	{
		int BaseAddress;
	public:
		AttachEffect(int address);
		int GetBaseAddress();
	};
	class Animation
	{
		int BaseAddress;
	public:
		Animation(int idoraddress);
		//support muiti-animprop(AP_XXXXXX)
		static void UnLock(int animprop);
		static void Lock();
		int GetBaseAddress();
		T_PROPERTY(FLOAT, CycleRate, __get_CycleRate, __set_CycleRate, 4);
		T_PROPERTY(FLOAT, Speed, __get_Speed, __set_Speed, 8);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x14);
		INT_PROPERTY(StartFrame, __get_StartFrame, __set_StartFrame, 0x18);
		INT_PROPERTY(FrameCount, __get_FrameCount, __set_FrameCount, 0x1C);
		INT_PROPERTY(FrameBasePose, __get_FrameBasePose, __set_FrameBasePose, 0x20);
		T_PROPERTY(FLOAT, XScale, __get_XScale, __set_XScale, 0x24);
		T_PROPERTY(FLOAT, XSlant, __get_XSlant, __set_XSlant, 0x28);
		T_PROPERTY(FLOAT, XOffset, __get_XOffset, __set_XOffset, 0x2C);
		T_PROPERTY(FLOAT, YScale, __get_YScale, __set_YScale, 0x30);
		T_PROPERTY(FLOAT, YSlant, __get_YSlant, __set_YSlant, 0x34);
		T_PROPERTY(FLOAT, YOffset, __get_YOffset, __set_YOffset, 0x38);
		Color GetColor();
		void SetColor(Color color);
		SPT<TrackInstance> GetTrackInstance(const char* trackName);
		INT_PROPERTY(CycleCount, __get_CycleCount, __set_CycleCount, 0x5C);
		T_PROPERTY(PaintState::PaintState, Paint, __get_Paint, __set_Paint, 0x98);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x9C);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		SPT<AttachEffect> AttachTo(int AttachmentID, float OffsetX, float OffsetY);
		void Die();
		void Play(const char* TrackName, int blendType, int loopType, float rate);
		void AssignRenderGroupToPrefix(byte RenderGroup, const char* TrackName);
		int FindTrackIndex(const char* trackName);
	};
	class Attachment
	{
		int BaseAddress;
	public:
		int GetBaseAddress();
		Attachment(int idoraddress);
		// TODO: check whether this function works properly.
		SPT<PVZ::Animation> GetAnimation();
		INT_READONLY_PROPERTY(Id, __get_Id, 0x308);
	};
	class TrackInstance
	{
		int BaseAddress;
	public:
		int GetBaseAddress();
		TrackInstance(int idoraddress);
		SPT<PVZ::Attachment> GetAttachment();
	};
	class Lawn
	{
		int BaseAddress;
	public:
		Lawn(int baseaddress);
		LawnType::LawnType GetGridType(int row, int column);
		void SetGridType(int row, int column, LawnType::LawnType type);
		RouteType::RouteType GetRouteType(int route);
		void SetRouteType(int route, RouteType::RouteType type);
		bool Plantable(int row, int column, PlantType::PlantType type);
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
		void GetAll(ZombieType::ZombieType* ztypes);
		void SetAll(ZombieType::ZombieType* ztypes, size_t length);
		ZombieType::ZombieType Get(int index);
		void Set(int index, ZombieType::ZombieType ztype);
		void Del(int index);
		void Add(ZombieType::ZombieType ztype);
		void AddAll(ZombieType::ZombieType* ztypes, int length);
	};
	// 鼠标对象(控制层面的鼠标)
	class Mouse
	{
		int BaseAddress;
	public:
		Mouse(int baseaddress);
		T_READONLY_PROPERTY(BOOLEAN, InGameArea, __get_InGameArea, 0xDC);
		INT_PROPERTY(X, __get_X, __set_X, 0xE0);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xE4);
		T_READONLY_PROPERTY(MouseClickState::MouseClickState, ClickState, __get_ClickState, 0xE8);
		void WMClick(short x, short y);
		void GameClick(int x, int y);
		void MoveTo(int x, int y);
	};
	class Zombie : public GameObject
	{
	public:
		Zombie(int indexoraddress);
		/*调用该函数后，对应的 GetAll()、基类的构造函数都会失效。
		因此，请在派生类中调用这个函数，并且为派生类单独撰写新的构造函数和 GetAll() 。
		另外，调用该函数后，新生成的存档与原版存档不兼容，请注意清理。 */
		static void SetMemSize(int NewSize, int NewCount);

		struct AccessoriesType1
		{
			ZombieAccessoriesType1::ZombieAccessoriesType1 Type;
			int Hp;
			int MaxHp;
		};
		struct AccessoriesType2
		{
			ZombieAccessoriesType2::ZombieAccessoriesType2 Type;
			int Hp;
			int MaxHp;
		};

		T_PROPERTY(ZombieType::ZombieType, Type, __get_Type, __set_Type, 0x24);
		T_PROPERTY(ZombieState::ZombieState, State, __get_State, __set_State, 0x28);
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x2C);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x30);
		T_READONLY_PROPERTY(FLOAT, Speed, __get_Speed, 0x34);
		void SetSpeed(float speed);
		T_READONLY_PROPERTY(BOOLEAN, ShowingTongue, __get_ShowingTongue, 0x50);
		T_READONLY_PROPERTY(BOOLEAN, Eating, __get_Eating, 0x51);
		void Light(int cs = 100);
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		INT_READONLY_PROPERTY(ZombieHeight, __get_ZombieHeight, 0x64);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x68);
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x74);
		INT_PROPERTY(BungeeColumn, __get_BungeeColumn, __set_BungeeColumn, 0x80);
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x84);
		void GetCollision(CollisionBox* collbox);
		void SetCollision(CollisionBox* collbox);
		void GetAttackCollision(CollisionBox* collbox);
		void SetAttackCollision(CollisionBox* collbox);
		INT_PROPERTY(DecelerateCountdown, __get_DecelerateCountdown, __set_DecelerateCountdown, 0xAC);
		INT_PROPERTY(FixedCountdown, __get_FixedCountdown, __set_FixedCountdown, 0xB0);
		INT_PROPERTY(FrozenCountdown, __get_FrozenCountdown, __set_FrozenCountdown, 0xB4);
		T_PROPERTY(BOOLEAN, Hypnotized, __get_Hypnotized, __set_Hypnotized, 0xB8);
		T_PROPERTY(BOOLEAN, Blowaway, __get_Blowaway, __set_Blowaway, 0xB9);
		T_PROPERTY(BOOLEAN, NotDying, __get_NotDying, __set_NotDying, 0xBA);
		T_READONLY_PROPERTY(BOOLEAN, HandBroken, __get_HandBroken, 0xBB);
		T_PROPERTY(BOOLEAN, SthinHandOrYetiLeft, __get_SthinHandOrYetiLeft, __set_SthinHandOrYetiLeft, 0xBC);
		T_PROPERTY(BOOLEAN, InWater, __get_InWater, __set_InWater, 0xBD);
		T_PROPERTY(BOOLEAN, GarlicBited, __get_GarlicBited, __set_GarlicBited, 0xBF);
		AccessoriesType1 GetAccessoriesType1();
		void SetAccessoriesType1(AccessoriesType1 acctype1);
		AccessoriesType2 GetAccessoriesType2();
		void SetAccessoriesType2(AccessoriesType2 acctype2);
		void GetBodyHp(int* hp, int* maxhp);
		void SetBodyHp(int hp, int maxhp);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0xEC);
		SPT<PVZ::Animation> GetAnimation();
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x11C);
		//临时变量 
		INT_PROPERTY(Temp, __get_Temp, __set_Temp, 0x12C);
		SPT<PVZ::Animation> GetSpecialHeadAnimation();
		void SetSpecialHeadAnimation(SPT<PVZ::Animation> anim);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x158);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Hit(int damage, DamageType::DamageType type = DamageType::Direct);
		void Hit(int damage, DamageFlags flags = DAMAGEF_NONE);
		// 忽略所有护甲只命中本体
		void HitBody(int damage, DamageType::DamageType type = DamageType::Direct);
		void HitBody(int damage, DamageFlags flags = DAMAGEF_NONE);
		void Blast();
		void Butter(int countdown);
		//减速僵尸，无法减速默认免疫减速的僵尸。 
		void Decelerate(int countdown);
		//冻结僵尸，无法冻结默认免疫冻结的僵尸。 
		//不造成冻结伤害，不影响减速时长。 
		void Froze(int countdown);
		void Hypnotize();
		void Remove();
		void RemoveWithLoot();
		//animPlayArg(APA_XXXXXX)
		void SetAnimation(LPCSTR animName, byte animPlayArg);
		void EquipBucket(int shield = 1100);
		void EquipCone(int shield = 370);
		void ReanimShowPrefix(const char* trackPrefix, int renderGroup);

		bool canDecelerate();
		bool canFroze();
		//@brief 判定僵尸是否能被指定索敌类型搜寻到。
		//@param range 索敌类型。
		//@param usepvzfunc 是否调用 pvz 内部函数。默认为 true。
		//@return 是否能被搜寻到。
		bool EffectedBy(DamageRangeFlags range, bool usepvzfunc = true);
	};
	class Projectile : public GameObject
	{
	public:
		Projectile(int indexoraddress);
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x30);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x34);
		T_PROPERTY(FLOAT, Height, __get_Height, __set_Height, 0x38);
		T_PROPERTY(FLOAT, XSpeed, __get_XSpeed, __set_XSpeed, 0x3C);
		T_PROPERTY(FLOAT, YSpeed, __get_YSpeed, __set_YSpeed, 0x40);
		T_PROPERTY(FLOAT, HeightSpeed, __get_HeightSpeed, __set_HeightSpeed, 0x44);
		T_PROPERTY(FLOAT, HeightAcceleration, __get_HeightAcceleration, __set_HeightAcceleration, 0x48);
		T_PROPERTY(FLOAT, ShadowY, __get_ShadowY, __ShadowY, 0x4C);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x50);
		T_PROPERTY(MotionType::MotionType, Motion, __get_Motion, __set_Motion, 0x58);
		T_PROPERTY(ProjectileType::ProjectileType, Type, __get_Type, __set_Type, 0x5C);
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x60);
		T_PROPERTY(FLOAT, RotationAngle, __get_RotationAngle, __set_RotationAngle, 0x68);
		T_PROPERTY(FLOAT, RotationSpeed, __get_RotationSpeed, __set_RotationSpeed, 0x6C);
		INT_PROPERTY(DamageAbility, __get_DamageAbility, __set_DamageAbility, 0x74);
		INT_PROPERTY(TracktargetId, __get_TracktargetId, __set_TracktargetId, 0x88);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x90);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void OnFire();
		void Remove();
	};
	class Plant : public GameObject
	{
	public:
		static const int MemSize = 0x14C;
		Plant(int indexoraddress);
		/*调用该函数后，对应的 GetAll()、基类的构造函数都会失效。
		因此，请在派生类中调用这个函数，并且为派生类单独撰写新的构造函数和 GetAll() 。
		另外，调用该函数后，新生成的存档与原版存档不兼容，请注意清理。 */
		static void SetMemSize(int NewSize, int NewCount);
		T_PROPERTY(PlantType::PlantType, Type, __get_Type, __set_Type, 0x24);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x28);
		T_PROPERTY(PlantState::PlantState, State, __get_State, __set_State, 0x3C);
		INT_PROPERTY(Hp, __get_Hp, __set_Hp, 0x40);
		INT_PROPERTY(MaxHp, __get_MaxHp, __set_MaxHp, 0x44);
		T_PROPERTY(BOOLEAN, Aggressive, __get_Aggressive, __set_Aggressive, 0x48);
		INT_PROPERTY(BloverDisappearCountdown, __get_BloverDisappearCountdown, __set_BloverDisappearCountdown, 0x4C);
		INT_PROPERTY(EffectiveCountdown, __get_EffectiveCountdown, __set_EffectiveCountdown, 0x50);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x54);
		INT_PROPERTY(ShootOrProductCountdown, __get_ShootOrProductCountdown, __set_ShootOrProductCountdown, 0x58);
		INT_PROPERTY(ShootOrProductInterval, __get_ShootOrProductInterval, __set_ShootOrProductInterval, 0x5C);
		INT_PROPERTY(ShootingCountdown, __get_ShootingCountdown, __set_ShootingCountdown, 0x90);
		SPT<PVZ::Animation> GetAnimationPart1();
		SPT<PVZ::Animation> GetAnimationPart2();
		SPT<PVZ::Animation> GetAnimationPart3();
		SPT<PVZ::Animation> GetAnimationPart4();
		SPT<PVZ::Animation> GetAnimationEyeBlink();
		SPT<PVZ::Animation> GetAnimationPotatoGlow();
		SPT<PVZ::Animation> GetAnimationSleep();
		void Light(int cs = 100);
		void Flash(int cs = 100);
		T_PROPERTY(FLOAT, ImageXOffset, __get_ImageXOffset, __set_ImageXOffset, 0xC0);
		T_PROPERTY(FLOAT, ImageYOffset, __get_ImageYOffset, __set_ImageYOffset, 0xC4);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x141);
		T_PROPERTY(BOOLEAN, Squash, __get_Squash, __set_Squash, 0x142);
		T_READONLY_PROPERTY(BOOLEAN, Sleeping, __get_Sleeping, 0x143);
		void SetSleeping(bool sleeping);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x148);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void CreateEffect();
		// 将植物定身为纸板（同 IZ），会让土豆地雷直接出土。
		void SetStatic();
		void Smash();
		int CalcLayer();
		void MoveTo(int row, int column);
		void Remove();
		SPT<PVZ::Projectile> Shoot(int targetid = -1);
		SPT<PVZ::Projectile> Shoot(MotionType::MotionType motiontype = MotionType::None, int targetid = -1, bool special = false);
		//animPlayArg(APA_XXXXXX)
		void SetAnimation(LPCSTR animName, byte animPlayArg, int imagespeed);
		class MagnetItem
		{
			int BaseAddress;
		public:
			MagnetItem(int address);
			T_PROPERTY(FLOAT, X, __get_X, __set_X, 0);
			T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 4);
			T_PROPERTY(FLOAT, DestOffsetX, __get_DestOffsetX, __set_DestOffsetX, 8);
			T_PROPERTY(FLOAT, DestOffsetY, __get_DestOffsetY, __set_DestOffsetY, 0xC);
			T_PROPERTY(MagnetItemType::MagnetItemType, Type, __get_Type, __set_Type, 0x10);
		};
		SPT<MagnetItem> GetMagnetItem(int num);
	};
	class GardenPlant
	{
		int BaseAddress;
	public:
		GardenPlant(int address);
		T_PROPERTY(PlantType::PlantType, Type, __get_Type, __set_Type, 8);
		T_PROPERTY(GardenScene::GardenScene, Location, __get_Location, __set_Location, 0xC);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x10);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		//GPD_LEFT or GPD_RIGTHT
		INT_PROPERTY(Direction, __get_Direction, __set_Direction, 0x18);
		T_PROPERTY(std::time_t, LastWateredTime, __get_LastWateredTime, __set_LastWateredTime, 0x20);
		INT_PROPERTY(Colour, __get_Colour, __set_Colour, 0x28);
		T_PROPERTY(GardenPlantState::GardenPlantState, State, __get_State, __set_State, 0x2C);
		INT_PROPERTY(WateredCount, __get_WateredCount, __set_WateredCount, 0x30);
		INT_PROPERTY(LevelUpWaterNeed, __get_LevelUpWaterNeed, __set_LevelUpWaterNeed, 0x34);
		T_PROPERTY(GardenPlantNeed::GardenPlantNeed, LevelUpNeed, __get_LevelUpNeed, __set_LevelUpNeed, 0x38);
		T_PROPERTY(std::time_t, LastGoldTime, __get_LastGoldTime, __set_LastGoldTime, 0x40);
		T_PROPERTY(std::time_t, LastGrowthTime, __get_LastGrowthTime, __set_LastGrowthTime, 0x48);
	};
	class Coin : public GameObject //Item
	{
	public:
		Coin(int indexoraddress);
		INT_READONLY_PROPERTY(ImageXVariation, __get_ImageXVariation, 8);
		INT_READONLY_PROPERTY(ImageYVariation, __get_ImageYVariation, 0xC);
		void GetCollision(CollisionBox* collbox);
		void SetCollision(CollisionBox* collbox);
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
		T_PROPERTY(FLOAT, Size, __get_Size, __set_Size, 0x34);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x38);
		INT_READONLY_PROPERTY(ExistedTime, __get_ExistedTime, 0x4C);
		T_PROPERTY(BOOLEAN, Collected, __get_Collected, __set_Collected, 0x50);
		T_PROPERTY(CoinType::CoinType, Type, __get_Type, __set_Type, 0x58);
		T_PROPERTY(CoinMotionType::CoinMotionType, Motion, __get_Motion, __set_Motion, 0x5C);
		SPT<PVZ::Attachment> GetAttachment();
		T_PROPERTY(CardType::CardType, ContentCard, __get_ContentCard, __set_ContentCard, 0x68);
		SPT<PVZ::GardenPlant> GetGardenPlant();
		T_PROPERTY(BOOLEAN, HasHalo, __get_HasHalo, __set_HasHalo, 0xC8);
		INT_READONLY_PROPERTY(Id, __get_Id, 0xD0);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Collect();
	};
	class Lawnmover
	{
		int BaseAddress;
	public:
		Lawnmover(int indexoraddress);
		int GetBaseAddress();
		INT_PROPERTY(X, __get_X, __set_X, 8);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xC);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x10);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		SPT<PVZ::Animation> GetAnimation();
		T_PROPERTY(LawnmoverState::LawnmoverState, State, __get_State, __set_State, 0x2C);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x30);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x31);
		T_PROPERTY(LawnmoverType::LawnmoverType, Type, __get_Type, __set_Type, 0x34);
		T_PROPERTY(FLOAT, YOffset, __get_YOffset, __set_YOffset, 0x38);
		INT_READONLY_PROPERTY(Id, __get_Id, 0x44);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Die();
	};
	class Griditem
	{
	protected:
		int BaseAddress;
	public:
		int GetBaseAddress();
		Griditem(int indexoraddress);
		SPT<PVZ::Board> GetBoard();
		T_PROPERTY(GriditemType::GriditemType, Type, __get_Type, __set_Type, 0x8);
		T_PROPERTY(GriditemState::GriditemState, State, __get_State, __set_State, 0xC);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x10);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x14);
		INT_PROPERTY(Layer, __get_Layer, __set_Layer, 0x1C);
		T_PROPERTY(BOOLEAN, NotExist, __get_NotExist, __set_NotExist, 0x20);
		INT_READONLY_PROPERTY(Id, __get_Id, 0xE8);
		READONLY_PROPERTY_BINDING(int, __get_Index, Id & 0xFFFF) Index;
		void Remove();
	};
	class Grave :public PVZ::Griditem
	{
	public:
		Grave(int indexoraddress) :Griditem(indexoraddress) {};
		INT_PROPERTY(AppearedValue, __get_AppearedValue, __set_AppearedValue, 0x18);
	};
	class Crater :public PVZ::Griditem
	{
	public:
		Crater(int indexoraddress) :Griditem(indexoraddress) {};
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x18);
	};
	class AquariumBrain :public PVZ::Griditem
	{
	public:
		AquariumBrain(int indexoraddress) :Griditem(indexoraddress) {};
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
	};
	class Snail :public PVZ::Griditem
	{
	public:
		Snail(int indexoraddress) :Griditem(indexoraddress) {};
		T_PROPERTY(FLOAT, X, __get_X, __set_X, 0x24);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
		T_PROPERTY(FLOAT, TargetX, __get_TargetX, __set_TargetX, 0x2C);
		T_PROPERTY(FLOAT, TargetY, __get_TargetY, __set_TargetY, 0x30);
	};
	class Vase :public PVZ::Griditem
	{
	public:
		Vase(int indexoraddress) :Griditem(indexoraddress) {};
		T_PROPERTY(VaseSkin::VaseSkin, Skin, __get_Skin, __set_Skin, 0xC);
		T_PROPERTY(ZombieType::ZombieType, ContentZombie, __get_ContentZombie, __set_ContentZombie, 0x3C);
		T_PROPERTY(PlantType::PlantType, ContentPlant, __get_ContentPlant, __set_ContentPlant, 0x40);
		T_PROPERTY(VaseContent::VaseContent, Content, __get_Content, __set_Content, 0x44);
		T_READONLY_PROPERTY(BOOLEAN, MouseEnter, __get_MouseEnter, 0x48);
		INT_PROPERTY(TransparentCountDown, __get_TransparentCountDown, __set_TransparentCountDown, 0x4C);
		INT_PROPERTY(Sun, __get_Sun, __set_Sun, 0x50);
		void Open();
	};
	class IZBrain :public PVZ::Griditem
	{
	public:
		IZBrain(int indexoraddress) :Griditem(indexoraddress) {};
		INT_PROPERTY(Hp, __get_Hp, __set_Hp, 0x18);
		T_PROPERTY(FLOAT, Y, __get_Y, __set_Y, 0x28);
	};
	// 在非传送门关卡中只有画面效果不会触发传送
	// 提供几个方法用于模拟传送门关卡中的传送效果
	class Portal :public PVZ::Griditem
	{
	public:
		Portal(int indexoraddress) :Griditem(indexoraddress) {};
		void Close();
		// 判定僵尸是否进入这个传送门
		bool isZombieIn(std::shared_ptr<PVZ::Zombie> zombie);
		// 获取僵尸从这个传送门出来时的X坐标
		int getZombieOutX();
		// 判定子弹是否进入这个传送门
		bool isProjectileIn(std::shared_ptr<PVZ::Projectile> projectile);
		// 获取子弹从这个传送门射出时的X坐标
		int getProjectileOutX();
	};
	class MousePointer : public GameObject//+138
	{
	public:
		MousePointer(int address);
		INT_PROPERTY(CardIndex, __get_CardIndex, __set_CardIndex, 0x24);
		T_PROPERTY(CardType::CardType, ContentCard, __get_ContentCard, __set_ContentCard, 0x28);
		T_PROPERTY(CardType::CardType, ContentCardImitative, __get_ContentCardImitative, __set_ContentCardImitative, 0x2C);
		T_PROPERTY(MouseType::MouseType, Type, __get_Type, __set_Type, 0x30);
		INT_PROPERTY(CoinID, __get_CoinID, __set_CoinID, 0x34);
		INT_PROPERTY(GlovePlantID, __get_GlovePlantID, __set_GlovePlantID, 0x38);
		INT_PROPERTY(ImitativePlantID, __get_ImitativePlantID, __set_ImitativePlantID, 0x3C);
		INT_PROPERTY(CobCannonID, __get_CobCannonID, __set_CobCannonID, 0x40);
		INT_PROPERTY(HammerDownCount, __get_HammerDownCount, __set_HammerDownCount, 0x44);
		SPT<PVZ::Animation> GetAnimation();
		READONLY_PROPERTY_BINDING(int, __get_Row, Memory::ReadPointer(PVZBASEADDRESS + 0x13C, 0x28)) Row;
		READONLY_PROPERTY_BINDING(int, __get_Column, Memory::ReadPointer(PVZBASEADDRESS + 0x13C, 0x24)) Column;
	};
	class Caption
	{
		int BaseAddress;
	public:
		Caption(int address);
		int GetBaseAddress();
		void GetText(char str[]);//str[0x80]
		void SetText(const char str[]);//str[0x80]
		INT_PROPERTY(DisappearCountdown, __get_DisappearCountdown, __set_DisappearCountdown, 0x88);
		T_PROPERTY(CaptionStyle::CaptionStyle, Style, __get_CaptionStyle, __set_CaptionStyle, 0x8C);
	};
	class CardSlot
	{
		int BaseAddress;
	public:
		CardSlot(int address);
		int GetBaseAddress();
		INT_PROPERTY(X, __get_X, __set_X, 8);
		INT_PROPERTY(Y, __get_Y, __set_Y, 0xC);
		INT_PROPERTY(CollisionLength, __get_CollisionLength, __set_CollisionLength, 0x10);
		T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
		INT_READONLY_PROPERTY(CardsCount, __get_CardsCount, 0x24);
		class SeedCard
		{
			int BaseAddress;
		public:
			SeedCard(int address);
			int GetBaseAddress();
			INT_PROPERTY(X, __get_X, __set_X, 0x8);
			INT_PROPERTY(Y, __get_Y, __set_Y, 0xC);
			void GetCollision(CollisionBox* collbox);
			void SetCollision(CollisionBox* collbox);
			T_PROPERTY(BOOLEAN, Visible, __get_Visible, __set_Visible, 0x18);
			INT_PROPERTY(CoolDown, __get_CoolDown, __set_CoolDown, 0x24); // 已冷却时间，从0开始
			INT_PROPERTY(CoolDownInterval, __get_CoolDownInterval, __set_CoolDownInterval, 0x28);
			INT_READONLY_PROPERTY(Index, __get_Index, 0x2C);
			INT_PROPERTY(XInConveyorBelt, __get_XInConveyorBelt, __set_XInConveyorBelt, 0x30);
			T_PROPERTY(CardType::CardType, ContentCard, __get_ContentCard, __set_ContentCard, 0x34);
			T_PROPERTY(CardType::CardType, ContentCardImitative, __get_ContentCardImitative, __set_ContentCardImitative, 0x38);
			INT_PROPERTY(SlotCountdown, __get_SlotCountdown, __set_SlotCountdown, 0x3C);
			T_PROPERTY(CardType::CardType, SlotType, __get_SlotType, __set_SlotType, 0x40);
			T_PROPERTY(FLOAT, SlotPosition, __get_SlotPosition, __set_SlotPosition, 0x44);
			T_PROPERTY(BOOLEAN, Enable, __get_Enable, __set_Enable, 0x48); // 该卡槽是否可点击
			T_PROPERTY(BOOLEAN, Active, __get_Active, __set_Active, 0x49); // 该卡槽是否正在CD
			INT_PROPERTY(UsageCount, __get_UsageCount, __set_UsageCount, 0x4C);
			// 该卡槽进入CD，持续时间为-1则为该卡槽的默认时间
			void EnterCoolDown(int duration = -1);
		};
		void SetCardsCount(int num);
		SPT<PVZ::CardSlot::SeedCard> GetCard(int index);
	};
	class Miscellaneous
	{
		int BaseAddress;
	public:
		Miscellaneous(int address);
		int GetBaseAddress();
		static const int MemSize = 0x0BC;
		/*请在派生类中调用这个函数。
		另外，调用该函数后，新生成的存档与原版存档不兼容，请注意清理。
		@return 是否修改成功。
		*/
		static bool SetMemSize(int NewSize);

		T_READONLY_PROPERTY(BOOLEAN, DragingPlant, __get_DragingPlant, 8);
		INT_READONLY_PROPERTY(DragingX, __get_DragingX, 0xC);
		INT_READONLY_PROPERTY(DragingY, __get_DragingY, 0x10);
		BOOLEAN HaveCrater(int row, int column);
		void SetCrater(int row, int column, BOOLEAN b);
		T_PROPERTY(BOOLEAN, UpgradedRepeater, __get_UpgradedRepeater, __set_UpgradedRepeater, 0x4A);
		T_PROPERTY(BOOLEAN, UpgradedFumeshroom, __get_UpgradedFumeshroom, __set_UpgradedFumeshroom, 0x4B);
		T_PROPERTY(BOOLEAN, UpgradedTallnut, __get_UpgradedTallnut, __set_UpgradedTallnut, 0x4C);
		T_PROPERTY(ChallengeState::ChallengeState, State, __get_State, __set_State, 0x54);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x58);
		INT_PROPERTY(ConveyorCountdown, __get_ConveyorCountdown, __set_ConveyorCountdown, 0x5C);
		INT_PROPERTY(LevelProcess, __get_LevelProcess, __set_LevelProcess, 0x60);
		T_PROPERTY(CardType::CardType, ConveyorLastCard, __get_ConveyorLastCard, __set_ConveyorLastCard, 0x68);
		INT_PROPERTY(Round, __get_Round, __set_Round, 0x6C);
		INT_PROPERTY(SlotMachineRollCount, __get_SlotMachineRollCount, __set_SlotMachineRollCount, 0x70);
		INT_READONLY_PROPERTY(VaseCount, __get_VaseCount, 0x0B0);
		INT_READONLY_PROPERTY(TreeOfWisdomTalkIndex, __get_TreeOfWisdomTalkIndex, 0x0B8);
	};
	class SaveData
	{
		int BaseAddress;
	public:
		SaveData(int baseaddress);
		int GetBaseAddress();
		void GetPVZUserName(char str[]);//str[12]
		INT_READONLY_PROPERTY(UserSwitchCount, __get_UserSwitchCount, 0x1C);
		INT_READONLY_PROPERTY(UserIndex, __get_UserIndex, 0x20);
		INT_PROPERTY(AdventureLevel, __get_AdventureLevel, __set_AdventureLevel, 0x24);
		INT_PROPERTY(Money, __get_Money, __set_Money, 0x28);
		INT_PROPERTY(AdventureFinishCount, __get_AdventureFinishCount, __set_AdventureFinishCount, 0x2C);
		INT_PROPERTY(TreeHight, __get_TreeHight, __set_TreeHight, 0xF4);
		BOOLEAN HavePurpleCard(CardType::CardType purplecard);
		T_PROPERTY(BOOLEAN, HaveImitater, __get_HaveImitater, __set_HaveImitater, 0x1E0);
		T_PROPERTY(BOOLEAN, HaveGoldenWatering, __get_HaveGoldenWatering, __set_HaveGoldenWatering, 0x1F4);
		INT_PROPERTY(Fertilizer, __get_Fertilizer, __set_Fertilizer, 0x1F8);//-1000
		INT_PROPERTY(BugSpray, __get_BugSpray, __set_BugSpray, 0x1FC);//-1000
		T_PROPERTY(BOOLEAN, HaveMusicBox, __get_HaveMusicBox, __set_HaveMusicBox, 0x200);
		T_PROPERTY(BOOLEAN, HaveGardeningGlove, __get_HaveGardeningGlove, __set_HaveGardeningGlove, 0x204);
		T_PROPERTY(BOOLEAN, HaveMushroomGarden, __get_HaveMushroomGarden, __set_HaveMushroomGarden, 0x208);
		T_PROPERTY(BOOLEAN, HaveWheelBarrow, __get_HaveWheelBarrow, __set_HaveWheelBarrow, 0x20C);
		T_PROPERTY(BOOLEAN, HaveSnail, __get_HaveSnail, __set_HaveSnail, 0x210);
		INT_PROPERTY(CardSlotNum, __get_CardSlotNum, __set_CardSlotNum, 0x214);
		T_PROPERTY(BOOLEAN, HavePoolCleaner, __get_HavePoolCleaner, __set_HavePoolCleaner, 0x218);
		T_PROPERTY(BOOLEAN, HaveRoofCleaner, __get_HaveRoofCleaner, __set_HaveRoofCleaner, 0x21C);
		INT_PROPERTY(LeftRakeCount, __get_LeftRakeCount, __set_LeftRakeCount, 0x220);
		T_PROPERTY(BOOLEAN, HaveAquarium, __get_HaveAquarium, __set_HaveAquarium, 0x224);
		INT_PROPERTY(Chocolate, __get_Chocolate, __set_Chocolate, 0x228);//-1000
		T_PROPERTY(BOOLEAN, HaveTreeOfWisdom, __get_HaveTreeOfWisdom, __set_HaveTreeOfWisdom, 0x22C);
		INT_PROPERTY(TreeFood, __get_TreeFood, __set_TreeFood, 0x230);//-1000
		T_PROPERTY(BOOLEAN, HaveWallnutFirstAid, __get_HaveWallnutFirstAid, __set_HaveWallnutFirstAid, 0x234);
		INT_READONLY_PROPERTY(GardenPlantCount, __get_GardenPlantCount, 0x350);
		class GardenPlant : public PVZ::GardenPlant
		{
		public:
			GardenPlant(int address) : PVZ::GardenPlant(address) {};
		};
		SPT<GardenPlant> GetGardenPlant(int index);
	};
	class Music
	{
		int BaseAddress;
	public:
		Music(int address);
		int GetBaseAddress();
		PROPERTY(MusicType::MusicType, __get_Type, __set_Type) Type;
		//MINGAM_ENABLE or MINGAM_DISABLE
		INT_PROPERTY(INGAMEable, __get_INGAMEable, __set_INGAMEable, 0x10);
		//MINGAME_STARTED or MINGAME_NOTSTARTED
		INT_PROPERTY(INGAMEStart, __get_INGAMEStart, __set_INGAMEStart, 0x18);
		INT_READONLY_PROPERTY(Tempo, __get_Tempo, 0x1C);
		INT_READONLY_PROPERTY(Ticks_Row, __get_Ticks_Row, 0x20);
		T_PROPERTY(INGAMEState::INGAMEState, State, __get_State, __set_State, 0x24);
		INT_PROPERTY(AttributeCountdown, __get_AttributeCountdown, __set_AttributeCountdown, 0x28);
		T_PROPERTY(INGAMEEffect::INGAMEEffect, INGAMEEffect, __get_INGAMEEffect, __set_INGAMEEffect, 0x2C);
	};
	//if anyone want a class for calling functions in bass.dll to totally control the music in game,just tell me

	class ZenGarden
	{
		int BaseAddress;
	public:
		ZenGarden(int address);
		int GetBaseAddress();
		SPT<PVZ::Board> GetBoard();
		T_PROPERTY(GardenScene::GardenScene, GardenType, __get_GardenType, __set_GardenType, 0x8);
		bool IsFull(bool consider_items);
		SPT<Snail> GetSnail();
	};

	class PlantDefinition
	{
		int BaseAddress;
	public:
		PlantDefinition(PlantType::PlantType type);
		T_READONLY_PROPERTY(CardType::CardType, Type, __get_Type, 0);
		T_READONLY_PROPERTY(AnimationType::AnimationType, AnimType, __get_AnimType, 8);
		INT_READONLY_PROPERTY(PacketID, __get_PacketID, 0xC);
		INT_PROPERTY(Cost, __get_Cost, __set_Cost, 0x10);
		INT_PROPERTY(Cooldown, __get_Cooldown, __set_Cooldown, 0x14);
		INT_PROPERTY(IsShooter, __get_IsShooter, __set_IsShooter, 0x18);
		INT_PROPERTY(AttackCooldown, __get_AttackCooldown, __set_AttackCooldown, 0x1C);
	};

	class ZombieDefinition
	{
		int BaseAddress;
	public:
		ZombieDefinition(ZombieType::ZombieType type);
		T_READONLY_PROPERTY(ZombieType::ZombieType, Type, __get_Type, 0);
		T_READONLY_PROPERTY(AnimationType::AnimationType, AnimType, __get_AnimType, 4);
		INT_PROPERTY(Value, __get_Value, __set_Value, 8);
		INT_PROPERTY(StartingLevel, __get_StartingLevel, __set_StartingLevel, 0xC);
		INT_PROPERTY(FirstAllowedWave, __get_FirstAllowedWave, __set_FirstAllowedWave, 0x10);
		INT_PROPERTY(PickWeight, __get_PickWeight, __set_PickWeight, 0x14);
	};

	class ProjectileDefinition
	{
		int BaseAddress;
	public:
		ProjectileDefinition(ProjectileType::ProjectileType type);
		T_READONLY_PROPERTY(ProjectileType::ProjectileType, Type, __get_Type, 0);
		INT_READONLY_PROPERTY(ImageRow, __get_ImageRow, 4);
		INT_PROPERTY(Damage, __get_Damage, __set_Damage, 8);
	};

	class ChallengeDefinition
	{
		int BaseAddress;
	public:
		ChallengeDefinition(PVZLevel::PVZLevel mode);
		T_READONLY_PROPERTY(PVZLevel::PVZLevel, Mode, __get_Mode, 0);
		INT_PROPERTY(IconIndex, __get_IconIndex, __set_IconIndex, 4);
		INT_PROPERTY(Page, __get_Page, __set_Page, 8);
		INT_PROPERTY(Row, __get_Row, __set_Row, 0x0C);
		INT_PROPERTY(Column, __get_Column, __set_Column, 0x10);
		INT_PROPERTY(NamePTR, __get_NamePTR, __set_NamePTR, 0x14);
	};

#pragma endregion

#pragma region methods

	SPT<Mouse> GetMouse();
	//若 BaseAddress 为 0，返回空指针
	SPT<Board> GetBoard();
	//若 BaseAddress 为 0，返回空指针
	SPT<SeedChooserScreen> GetSeedChooserScreen();
	SPT<SaveData> GetSaveData();
	SPT<Music> GetMusic();
	SPT<ZenGarden> GetZenGarden();
	SPT<PlantDefinition> GetPlantDefinition(PlantType::PlantType type);
	SPT<ZombieDefinition> GetZombieDefinition(ZombieType::ZombieType type);
	SPT<ProjectileDefinition> GetProjectileDefinition(ProjectileType::ProjectileType type);
	SPT<ChallengeDefinition> GetChallengeDefinition(PVZLevel::PVZLevel mode);

#pragma endregion

};