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

	extern DWORD pointerAddress;
	extern DWORD imageFontAddress;
	extern DWORD colorAddress;
	extern DWORD tempAddress;
	extern DWORD codeAddress;
	extern DWORD dataAddress;

	// 在屏幕上绘制所有字符串
	// 需要与DrawUITopEvent配合使用
	void writeString(std::vector<String> strings);
	
	// 一个page可以存放最多8个String结构体
	// 请根据自己的实际需要申请足够长的结构体
	void init(int pages);
}