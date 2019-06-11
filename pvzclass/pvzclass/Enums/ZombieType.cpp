#include "ZombieType.h"

const char* ZombieType::ToString(ZombieType zombiet)
{
	switch (zombiet)
	{
	case ZombieType::None:
		return "ZombieTypeNone";
	case ZombieType::Zombie:
		return "Zombie";
	case ZombieType::FlagZombie:
		return "FlagZombie";
	case ZombieType::ConeheadZombie:
		return "ConeheadZombie";
	case ZombieType::PoleVaultingZombie:
		return "PoleVaultingZombie";
	case ZombieType::BucketheadZombie:
		return "BucketheadZombie";
	case ZombieType::NewspaperZombie:
		return "NewspaperZombie";
	case ZombieType::ScreenDoorZombie:
		return "ScreenDoorZombie";
	case ZombieType::FootballZombie:
		return "FootballZombie";
	case ZombieType::DancingZombie:
		return "DancingZombie";
	case ZombieType::BackupDancer:
		return "BackupDancer";
	case ZombieType::DuckyTubeZombie:
		return "DuckyTubeZombie";
	case ZombieType::SnorkedZombie:
		return "SnorkedZombie";
	case ZombieType::Zomboin:
		return "Zomboin";
	case ZombieType::ZombieBobsledTeam:
		return "ZombieBobsledTeam";
	case ZombieType::DolphinRiderZombie:
		return "DolphinRiderZombie";
	case ZombieType::JackintheboxZombie:
		return "JackintheboxZombie";
	case ZombieType::BalloonZombie:
		return "BalloonZombie";
	case ZombieType::DiggerZombie:
		return "DiggerZombie";
	case ZombieType::PogoZombie:
		return "PogoZombie";
	case ZombieType::ZombieYeti:
		return "ZombieYeti";
	case ZombieType::BungeeZombie:
		return "BungeeZombie";
	case ZombieType::LadderZombie:
		return "LadderZombie";
	case ZombieType::CatapultZombie:
		return "CatapultZombie";
	case ZombieType::Gargantuar:
		return "Gargantuar";
	case ZombieType::Imp:
		return "Imp";
	case ZombieType::DrZomboss:
		return "DrZomboss";
	case ZombieType::PeashooterZombie:
		return "PeashooterZombie";
	case ZombieType::WallnutZombie:
		return "WallnutZombie";
	case ZombieType::JalapenoZombie:
		return "JalapenoZombie";
	case ZombieType::GatlingPeaZombie:
		return "GatlingPeaZombie";
	case ZombieType::SquashZombie:
		return "SquashZombie";
	case ZombieType::TallnutZombie:
		return "TallnutZombie";
	case ZombieType::Gigagargantuar:
		return "Gigagargantuar";
	default:
		return "InValid_Value_Of_ZombieType";
	}
}
