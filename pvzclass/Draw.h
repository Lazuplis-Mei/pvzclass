#pragma once
#include "PVZ.h"
#include <vector>
#include <algorithm>

namespace Draw
{
	// 加载字体，由于汉化版的特殊处理，这个函数实际上调用的是计算字符串长度
	void StringWidth(std::string *s, DWORD imageFontAddress);

	// 设置字体颜色
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD graphics);

	// 在指定位置绘制字体
	void DrawString(DWORD x, DWORD y, std::string *s, DWORD graphics);
}