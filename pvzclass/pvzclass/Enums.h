
#ifdef ENUMSTRING
namespace enumstring
{
#define VNAME(var) #var
#define IDENTIFIER(name) const char* name[]
#else
#undef VNAME
#undef IDENTIFIER
#define VNAME(var) var
#define IDENTIFIER(name) enum name
#endif

IDENTIFIER(PVZVersion)
{
	VNAME(V1_0_0_1051),
	VNAME(V1_2_0_1065),
	VNAME(V1_2_0_1073),
	VNAME(中文年度加强版),
	VNAME(粘度汗化版),
	VNAME(UnknowOrNotPVZ),
};

IDENTIFIER(PVZLevel)
{
	VNAME(Adventure),
	VNAME(Survival_Day),
	VNAME(Survival_Night),
	VNAME(Survival_Pool),
	VNAME(Survival_Fog),
	VNAME(Survival_Roof),
	VNAME(Survival_Day_Hard),
	VNAME(Survival_Night_Hard),
	VNAME(Survival_Pool_Hard),
	VNAME(Survival_Fog_Hard),
	VNAME(Survival_Roof_Hard),
	VNAME(Survival_Day_Endless),
	VNAME(Survival_Night_Endless),
	VNAME(Survival_Pool_Endless),
	VNAME(Survival_Fog_Endless),
	VNAME(Survival_Roof_Endless),
	VNAME(ZomBotany),
	VNAME(Wallnut_Bowling),
	VNAME(Slot_Machine),
	VNAME(It_s_RainingSeeds),
	VNAME(Beghouled),
	VNAME(Invisighoul),
	VNAME(Seeing_Stars),
	VNAME(Zombiguarium),
	VNAME(Beghouled_Twist),
	VNAME(Big_Trouble_Little_Zombie),
	VNAME(Portal_Combat),
	VNAME(Colum_Like_You_See_Em),
	VNAME(Bobsied_Bonanza),
	VNAME(Zombie_Nimble_Zombie_Quick),
	VNAME(Wharka_Zombie),
	VNAME(Last_Stand),
	VNAME(Zombotany2),
	VNAME(Wallnut_Bowling2),
	VNAME(Pogo_Party),
	VNAME(Dr_Zomboss_s_Revenge),
	VNAME(Art_Challenge_Wallnut),
	VNAME(Sunny_Day),
	VNAME(Unsodded),
	VNAME(Big_Time),
	VNAME(Art_Challenge_Sunflower),
	VNAME(Air_Raid),
	VNAME(Ice_Level),
	VNAME(Zen_Garden),
	VNAME(High_Gravity),
	VNAME(Grave_Danger),
	VNAME(Can_You_DigIt),
	VNAME(Dark_Stormy_Night),
	VNAME(Bungee_Blitz),
	VNAME(Squirrel),
	VNAME(Treeof_Wisdom),
	VNAME(Vasebreaker),
	VNAME(To_the_Left),
	VNAME(Third_Vase),
	VNAME(Chain_Rection),
	VNAME(Mis_forM_etal),
	VNAME(Scary_Potter),
	VNAME(Hokey_Pokey),
	VNAME(Another_Chain_Rection),
	VNAME(Aceof_Vace),
	VNAME(Vasebreaker_Endless),
	VNAME(I_Zombie),
	VNAME(I_ZombieToo),
	VNAME(IZ_CanYouDigIt),
	VNAME(Totally_Nuts),
	VNAME(Dead_Zeppelin),
	VNAME(Me_Smash),
	VNAME(Zom_Boogie),
	VNAME(Three_Hit_Wonder),
	VNAME(All_your_brain_z_r_belong_to_us),
	VNAME(I_Zombie_Endless),
	VNAME(Upsell),
	VNAME(Intro),
};

IDENTIFIER(PVZGameState)
{
	VNAME(Loading),
	VNAME(MainMenu),
	VNAME(Prepare),
	VNAME(Playing),
	VNAME(Losing),
	VNAME(Prize),
	VNAME(MVPlaying),
	VNAME(SelectingLevel),
};

IDENTIFIER(LawnType)
{
#ifdef ENUMSTRING
	"LawnTypeNone",
	"Grass",
#else
	LawnTypeNone = -1,
	Grass = 1,
#endif
	VNAME(_Unsodded),
	VNAME(Water),
};

IDENTIFIER(RouteType)
{
#ifdef ENUMSTRING
	"RouteTypeNone",
#else
	RouteTypeNone = -1,
#endif
	VNAME(NoZombie),
	VNAME(Land),
	VNAME(Pool),
};

IDENTIFIER(MouseClickState)
{
	VNAME(MouseClickStateNone),
		VNAME(LButton),
		VNAME(RButton),
		VNAME(LRButton),
		VNAME(MidButton),
		VNAME(LMidButton),
		VNAME(RMidButton),
		VNAME(LRMidButton),
};

IDENTIFIER(ZombieType)
{
#ifdef ENUMSTRING
	"ZombieTypeNone",
#else
	ZombieTypeNone = -1,
#endif
	VNAME(Zombie),
	VNAME(FlagZombie),
	VNAME(ConeheadZombie),
	VNAME(PoleVaultingZombie),
	VNAME(BucketheadZombie),
	VNAME(NewspaperZombie),
	VNAME(ScreenDoorZombie),
	VNAME(FootballZombie),
	VNAME(DancingZombie),
	VNAME(BackupDancer),
	VNAME(DuckyTubeZombie),
	VNAME(SnorkedZombie),
	VNAME(Zomboin),
	VNAME(ZombieBobsledTeam),
	VNAME(DolphinRiderZombie),
	VNAME(JackintheboxZombie),
	VNAME(BalloonZombie),
	VNAME(DiggerZombie),
	VNAME(PogoZombie),
	VNAME(ZombieYeti),
	VNAME(BungeeZombie),
	VNAME(LadderZombie),
	VNAME(CatapultZombie),
	VNAME(Gargantuar),
	VNAME(Imp),
	VNAME(DrZomboss),
	VNAME(PeashooterZombie),
	VNAME(WallnutZombie),
	VNAME(JalapenoZombie),
	VNAME(GatlingPeaZombie),
	VNAME(SquashZombie),
	VNAME(TallnutZombie),
	VNAME(Gigagargantuar),
};

IDENTIFIER(SceneType)
{
	VNAME(Day),
	VNAME(Night),
	VNAME(Pool_Scene),
	VNAME(Fog),
	VNAME(Roof),
	VNAME(MoonNight),
	VNAME(MushroomGarden),
	VNAME(ZenGarden),
	VNAME(Aquarium),
	VNAME(TreeofWisdom),
};

IDENTIFIER(DebugModeType)
{
	VNAME(DebugModeTypeNone),
	VNAME(ZombieSpawningDebug),
	VNAME(MusicDebug),
	VNAME(MemoryDebug),
	VNAME(CollisionDebug),
};

IDENTIFIER(ZombieAccessoriesType1)
{
	VNAME(ZombieAccessoriesType1None),
	VNAME(RoadCone),
	VNAME(Bucket),
	VNAME(FootballCap),
	VNAME(MinerHat),
	VNAME(Sled),
	VNAME(Wallnut),
	VNAME(Tallnut),
};

IDENTIFIER(ZombieAccessoriesType2)
{
	VNAME(ZombieAccessoriesType2None),
	VNAME(ScreenDoor),
	VNAME(Newspaper),
	VNAME(Ladder),
};

IDENTIFIER(DamageType)
{
	VNAME(Direct),
	VNAME(Not_Direct),
	VNAME(Sputter),
#ifdef ENUMSTRING
		"Direct_Ice",
#else
		Direct_Ice = 4,
#endif
	VNAME(Not_Direct_Ice),
	VNAME(Sputter_Ice),
};

IDENTIFIER(PlantType)
{
#ifdef ENUMSTRING
	"PlantTypeNone",
#else
	PlantTypeNone = -1,
#endif
	VNAME(Peashooter),
	VNAME(Sunflower),
	VNAME(CherryBomb),
	VNAME(Wallnut_Plant),
	VNAME(PotatoMine),
	VNAME(SnowPea),
	VNAME(Chomper),
	VNAME(Repeater),
	VNAME(Puffshroon),
	VNAME(Sunshroon),
	VNAME(Fumeshroon),
	VNAME(CraveBuster),
	VNAME(Hypnoshroon),
	VNAME(Scaredyshroon),
	VNAME(Iceshroon),
	VNAME(Doomshroon),
	VNAME(LilyPad),
	VNAME(Squash),
	VNAME(Threepeater),
	VNAME(TangleKelp),
	VNAME(Jalapeno),
	VNAME(Spickweed),
	VNAME(Tochwood),
	VNAME(Tallnut_Plant),
	VNAME(Seashroon),
	VNAME(Plantern),
	VNAME(Cactus),
	VNAME(Blover),
	VNAME(SplitPea),
	VNAME(Starfruit),
	VNAME(Pumplin),
	VNAME(Magnetshroom),
	VNAME(Cabbagepult),
	VNAME(FlowerPot),
	VNAME(Kernelpult),
	VNAME(CoffeeBean),
	VNAME(Garlic),
	VNAME(UmbrellaLeaf),
	VNAME(Marigold),
	VNAME(Melonpult),
	VNAME(GatlingPea),
	VNAME(TwinSunflower),
	VNAME(Gloomshroom),
	VNAME(Cattail),
	VNAME(WinterMelon),
	VNAME(GoldMagnet),
	VNAME(Spikerock),
	VNAME(CobCannon),
	VNAME(Imitater),
	VNAME(Explodenut),
	VNAME(GiantWallnut),
	VNAME(Sprout),
	VNAME(LeftRepeater),
};

#ifdef ENUMSTRING
const char* PlantEffectType[]
{
	"CherryBombEffect",
	"PotatoMineEffect",
	"IceshroonEffect",
	"DoomshroonEffect",
	"JalapenoEffect",
	"BloverEffect",
};
#else
enum PlantEffectType
{
	CherryBombEffect = 2,
	PotatoMineEffect = 4,
	IceshroonEffect = 14,
	DoomshroonEffect = 15,
	JalapenoEffect = 20,
	BloverEffect = 27,
};
#endif

IDENTIFIER(MotionType)
{
	VNAME(MotionTypeDirect),
	VNAME(Throw),
	VNAME(Slide),
#ifdef ENUMSTRING
		"Left",
		"LeftSlide",
#else
		Left = 4,
		LeftSlide = 6,
#endif
	VNAME(Float),
	VNAME(Slow),
	VNAME(Track),
};

IDENTIFIER(ProjectileType)
{
	VNAME(Pea),
	VNAME(ProjectileSnowPea),
	VNAME(Cabbage),
	VNAME(Melon),
	VNAME(Puff),
	VNAME(ProjectileWinterMelon),
	VNAME(FirePea),
	VNAME(Star),
	VNAME(ProjectileCactus),
	VNAME(Basketball),
	VNAME(Kernel),
	VNAME(ProjectileCobCannon),
	VNAME(Butter),
	VNAME(ZombiePea),
};

IDENTIFIER(CoinType)
{
#ifdef ENUMSTRING
	"SilverDollar",
#else
	SilverDollar = 1,
#endif
	VNAME(GoldDollar),
	VNAME(Diamond),
	VNAME(NormalSun),
	VNAME(MiniSun),
	VNAME(LargeSun),
#ifdef ENUMSTRING
	"Trophy",
	"Note",
#else
	Trophy = 8,
	Note = 15,
#endif
	VNAME(PlantCard),
	VNAME(PlantPresent),
	VNAME(MoneyBag),
};

IDENTIFIER(CoinMotionType)
{
	VNAME(Fastfall),
	VNAME(Slowfall),
	VNAME(Product),
	VNAME(Spray),
	VNAME(Collected),
	VNAME(DelayCollected),
};

#ifndef ENUMSTRING
namespace CardType
{
#endif
	IDENTIFIER(CardType)
	{
#ifdef ENUMSTRING
		"CardTypeNone",
#else
		CardTypeNone = -1,
#endif
			VNAME(Peashooter),
			VNAME(Sunflower),
			VNAME(CherryBomb),
			VNAME(Wallnut_Plant),
			VNAME(PotatoMine),
			VNAME(SnowPea),
			VNAME(Chomper),
			VNAME(Repeater),
			VNAME(Puffshroon),
			VNAME(Sunshroon),
			VNAME(Fumeshroon),
			VNAME(CraveBuster),
			VNAME(Hypnoshroon),
			VNAME(Scaredyshroon),
			VNAME(Iceshroon),
			VNAME(Doomshroon),
			VNAME(LilyPad),
			VNAME(Squash),
			VNAME(Threepeater),
			VNAME(TangleKelp),
			VNAME(Jalapeno),
			VNAME(Spickweed),
			VNAME(Tochwood),
			VNAME(Tallnut_Plant),
			VNAME(Seashroon),
			VNAME(Plantern),
			VNAME(Cactus),
			VNAME(Blover),
			VNAME(SplitPea),
			VNAME(Starfruit),
			VNAME(Pumplin),
			VNAME(Magnetshroom),
			VNAME(Cabbagepult),
			VNAME(FlowerPot),
			VNAME(Kernelpult),
			VNAME(CoffeeBean),
			VNAME(Garlic),
			VNAME(UmbrellaLeaf),
			VNAME(Marigold),
			VNAME(Melonpult),
			VNAME(GatlingPea),
			VNAME(TwinSunflower),
			VNAME(Gloomshroom),
			VNAME(Cattail),
			VNAME(WinterMelon),
			VNAME(GoldMagnet),
			VNAME(Spikerock),
			VNAME(CobCannon),
			VNAME(Imitater),
			VNAME(Explodenut),
			VNAME(GiantWallnut),
			VNAME(Sprout),
			VNAME(LeftRepeater),
#ifdef ENUMSTRING
			"Refresh",
#else
			Refresh = 54,
#endif
			VNAME(Crater),
			VNAME(Sun),
			VNAME(Diamond),
			VNAME(SnorkedZombie),
			VNAME(Trophy),
			VNAME(Zombie),
			VNAME(ConeheadZombie),
			VNAME(PoleVaultingZombie),
			VNAME(BucketheadZombie),
			VNAME(LadderZombie),
			VNAME(DiggerZombie),
			VNAME(BungeeZombie),
			VNAME(FootballZombie),
			VNAME(BalloonZombie),
			VNAME(ScreenDoorZombie),
			VNAME(Zomboin),
			VNAME(PogoZombie),
			VNAME(DancingZombie),
			VNAME(Gigagargantuar),
			VNAME(Imp),
	};
#ifndef ENUMSTRING
}
#endif

IDENTIFIER(LawnmoverType)
{
	VNAME(LawnCleaner),
	VNAME(PoolCleaner),
	VNAME(RoofCleaner),
	VNAME(Trickedout),
};

#ifdef ENUMSTRING
const char* GriditemType[]
{
	"Grave",
	"Crater",
	"Ladder",
	"PortalBlue",
	"PortalYellow",
	"Brain",
	"Vase",
	"Rake",
};
#else
enum GriditemType
{
	Grave = 1,
	Crater,
	GriditemLadder,
	PortalBlue,
	PortalYellow,
	Brain = 6,
	Vase,
	Rake = 11,
};
#endif

#ifdef ENUMSTRING
const char* VaseSkin[]
{
	"Unknow",
	"Leaf",
	"Zombie",
};
#else
enum VaseSkin
{
	Unknow = 3,
	Leaf,
	Zombie,
};
#endif

IDENTIFIER(VaseContent)
{
	VNAME(VaseContentNone),
	VNAME(VaseContentPlant),
	VNAME(VaseContentZombie),
	VNAME(VaseContentSun),
};

IDENTIFIER(MouseType)
{
	VNAME(MouseTypeNone),
	VNAME(Card),
#ifdef ENUMSTRING
	"Shovel",
	"Crosshair",
#else
	Shovel = 6,
	Crosshair = 8,
#endif
	VNAME(Watering),
	VNAME(GoldenWatering),
	VNAME(Fertilizer),
	VNAME(BugSpray),
	VNAME(Phonograph),
	VNAME(Chocolate),
	VNAME(GardeningGlove),
	VNAME(Sell),
	VNAME(WheelBarrow),
	VNAME(TreeFood),
};



#ifdef ENUMSTRING
};
#endif