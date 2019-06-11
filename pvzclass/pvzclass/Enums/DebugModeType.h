#pragma once
namespace DebugModeType
{

	enum DebugModeType
	{
		None,
		ZombieSpawningDebug,
		MusicDebug,
		MemoryDebug,
		CollisionDebug,
	};

	extern const char* ToString(DebugModeType debugmt);

}