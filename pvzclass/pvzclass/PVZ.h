#pragma once
#include <windows.h>
#include "Enums.h"

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
		template <class T>
		inline static T ReadMemory(int address)
		{
			T buffer;
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
		static void IngectDll(LPCSTR dllname);
	};

#pragma endregion

#pragma region properties

	READONLY_PROPERTY(
		const char*,
		__get_Version) Version;
	READONLY_PROPERTY(
		PVZVersion,
		__get_GameVersion) GameVersion;
	PROPERTY(
		double,
		__get_MusicVolume,
		__set_MusicVolume) MusicVolume;//range[0,1]
	PROPERTY(
		double,
		__get_SoundFXVolume,
		__set_SoundFXVolume) SoundFXVolume;//range[0,1]
	INT_READONLY_PROPERTY(
		ZombiesCount, 
		__get_ZombiesCount, 
		0xA0);
	INT_READONLY_PROPERTY(
		PlantsCount,
		__get_PlantsCount,
		0xBC);
	INT_READONLY_PROPERTY(
		ProjectilesCount,
		__get_ProjectilesCount,
		0xD8);
	INT_READONLY_PROPERTY(
		CoinsCount,
		__get_CoinsCount,
		0xF4);
	INT_READONLY_PROPERTY(
		LawnmoversCount,
		__get_LawnmoversCount,
		0x110);
	INT_READONLY_PROPERTY(
		GriditemsCount,
		__get_GriditemsCount,
		0x12C);
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
	INT_PROPERTY(
		ViewX,
		__get_ViewX,
		__set_ViewX,
		0x30);
	INT_PROPERTY(
		ViewY,
		__get_ViewY,
		__set_ViewY,
		0x34);
	INT_PROPERTY(
		ViewLength,
		__get_ViewLength,
		__set_ViewLength,
		0x38);
	INT_PROPERTY(
		ViewHeight,
		__get_ViewHeight,
		__set_ViewHeight,
		0x3C);
	T_PROPERTY(
		BOOLEAN,
		GamePaused,
		__get_GamePaused,
		__set_GamePaused,
		0x164);
	INT_PROPERTY(
		Sun,
		__get_Sun,
		__set_Sun,
		0x5560);
	INT_PROPERTY(
		SunDropCountdown,
		__get_SunDropCountdown,
		__set_SunDropCountdown,
		0x5538);
	INT_PROPERTY(
		SunDropCount,
		__get_SunDropCount,
		__set_SunDropCount,
		0x553C);
	PROPERTY(
		SceneType,
		__get_LevelScene,
		__set_LevelScene) LevelScene;


#pragma endregion

#pragma region classes

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

		READONLY_PROPERTY(
			int,
			__get_Count) Count;

		void GetAll(ZombieType* ztypes);
		void SetAll(ZombieType* ztypes, size_t length);
		ZombieType Get(int index);
		void Set(int index, ZombieType ztype);
		void Del(int index);
		void Add(ZombieType ztype);
	};
	
#pragma endregion

#pragma region methods

	Lawn* GetLawn();
	Icetrace* GetIcetrace();
	Wave* GetWave(int index);
	void GetZombieSeed(ZombieType* ztypes);
	void Earthquake(int horizontalAmplitude = 2, int verticalAmplitude = 4, int duration = 20);

#pragma endregion


};
