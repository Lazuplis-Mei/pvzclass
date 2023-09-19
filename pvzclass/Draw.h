#pragma once
#include "PVZ.h"
#include <vector>
#include <algorithm>

namespace Draw
{
	// 在(x,y)展示出指定size和rgb的字符串，字符串最长为100
	struct String
	{
		int x, y, size, red, green, blue;
		char s[100];
	};

	void writeString(DWORD address, std::vector<String> strings);
}