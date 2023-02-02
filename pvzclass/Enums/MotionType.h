#pragma once
namespace MotionType
{

	enum MotionType
	{
		None = -1,
		Direct = 0,
		Throw,
		Slide,
		Left = 4,
		ShortDirect,
		LeftSlide,
		Float,
		Slow,
		Track,
	};

	extern const char* ToString(MotionType motiont);

}