#pragma once
namespace MouseClickState
{

	enum MouseClickState
	{
		None,
		LButton,
		RButton,
		LRButton,
		MidButto,
		LMidButton,
		RMidButton,
		LRMidButton,
	};

	extern const char* ToString(MouseClickState mousecs);

}