#pragma once
namespace LawnmoverState
{

	enum LawnmoverState
	{
		RollingIn,
		Ready,
		Triggered,
		Squished,
	};

	extern const char* ToString(LawnmoverState lawnmovert);

}