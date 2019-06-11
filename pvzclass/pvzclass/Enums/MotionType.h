#pragma once
namespace MotionType
{

	enum MotionType
	{
		Direct,
		Throw,
		Slide,
		Left = 4,
		LeftSlide = 6,
		Float,
		Slow,
		Track,
	};

	extern const char* ToString(MotionType motiont);

}