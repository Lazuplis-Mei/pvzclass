namespace PVZ
{
	//判定僵尸是否符合指定条件的标志位。
	typedef unsigned char DamageRangeFlags;

	//是否位于地面上（或水面上）。
	const DamageRangeFlags DAMAGES_GROUND = (1 << 0);
	//是否飞行。
	const DamageRangeFlags DAMAGES_FLYING = (1 << 1);
	//是否潜水。
	const DamageRangeFlags DAMAGES_SUBMERGED = (1 << 2);
	//Deprecated
	const DamageRangeFlags DAMAGES_DOG = (1 << 3);
	//是否正在落地（或出土）。
	const DamageRangeFlags DAMAGES_OFF_GROUND = (1 << 4);
	//是否考虑已被击杀的僵尸。
	const DamageRangeFlags DAMAGES_DYING = (1 << 5);
	//是否位于地下。
	const DamageRangeFlags DAMAGES_UNDERGROUND = (1 << 6);
	//是否被魅惑。
	const DamageRangeFlags DAMAGES_HYPNOTIZED = (1 << 7);

	//全体未被魅惑的僵尸。
	const DamageRangeFlags DAMAGES_ALL = DAMAGES_GROUND | DAMAGES_FLYING
		| DAMAGES_SUBMERGED | DAMAGES_DOG | DAMAGES_OFF_GROUND | DAMAGES_DYING | DAMAGES_UNDERGROUND;
	//全体被魅惑的僵尸。
	const DamageRangeFlags DAMAGES_ALL_HYPNOTIZED = DAMAGES_HYPNOTIZED | DAMAGES_ALL;
}