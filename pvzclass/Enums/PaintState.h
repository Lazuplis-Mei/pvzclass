#pragma once
namespace PaintState
{
	enum PaintState
	{
		Normal = -1,
		LightGary,
		Gary,
		Cover,
	};

	extern const char* ToString(PaintState paints);

}