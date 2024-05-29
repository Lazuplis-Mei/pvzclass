#pragma once
#include "PVZ.h"
#include <vector>
#include <algorithm>

// 请与DrawUITopEvent配合使用
namespace Draw
{
	// 将字符数组转化为字符串，参数为字符数组的地址，返回值为字符串的地址
	void ToString(DWORD fromAddress, DWORD toAddress);

	// 加载字体，由于汉化版的特殊处理，这个函数实际上调用的是计算字符串长度
	void StringWidth(DWORD stringAddress, DWORD imageFontAddress);

	// 设置字体颜色
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD colorAddress, DWORD graphics);

	// 在指定位置绘制字体
	void DrawString(DWORD x, DWORD y, DWORD stringAddress, DWORD graphics);

	// 在指定位置绘制图片
	void DrawImage(DWORD x, DWORD y, DWORD imageAddress, DWORD graphics);
}