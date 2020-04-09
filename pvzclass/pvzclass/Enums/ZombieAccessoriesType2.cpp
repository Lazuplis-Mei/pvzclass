#include "ZombieAccessoriesType2.h"

const char* ZombieAccessoriesType2::ToString(ZombieAccessoriesType2 zombieat2)
{
	switch (zombieat2)
	{
	case ZombieAccessoriesType2::ZombieAccessoriesType2None:
		return "ZombieAccessoriesType2None";
	case ZombieAccessoriesType2::ScreenDoor:
		return "ScreenDoor";
	case ZombieAccessoriesType2::Newspaper:
		return "Newspaper";
	case ZombieAccessoriesType2::Ladder:
		return "Ladder";
	default:
		return "InValid_Value_Of_ZombieAccessoriesType2";
	}
}
