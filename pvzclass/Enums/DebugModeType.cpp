#include "DebugModeType.h"

const char* DebugModeType::ToString(DebugModeType debugmt)
{
	switch (debugmt)
	{
	case DebugModeType::None:
		return "DebugModeTypeNone";
	case DebugModeType::ZombieSpawningDebug:
		return "ZombieSpawningDebug";
	case DebugModeType::MusicDebug:
		return "MusicDebug";
	case DebugModeType::MemoryDebug:
		return "MemoryDebug";
	case DebugModeType::CollisionDebug:
		return "CollisionDebug";
	default:
		return "InValid_Value_Of_DebugModeType";
	}
}
