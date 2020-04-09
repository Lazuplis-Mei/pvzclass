#pragma once
namespace INGAMEEffect
{

	enum INGAMEEffect
	{
		None,
		FadeIn,
		Completed,
		FadeOut,
		Disappeared,
	};

	extern const char* ToString(INGAMEEffect ingamee);

}