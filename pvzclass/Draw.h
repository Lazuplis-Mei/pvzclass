#pragma once
#include "PVZ.h"

// 请与DrawUITopEvent配合使用
namespace Draw
{
	typedef DWORD PString;
	typedef DWORD PSharedImageRef;
	typedef DWORD PImage;
	extern BYTE color[16];

	// 将字符数组转化为字符串
	PString ToString(const char* str);

	// 将字符串转化为字符数组
	char* ToChar(PString str);

	// 加载字体，由于汉化版的特殊处理，这个函数实际上调用的是计算字符串长度
	void StringWidth(PString str, DWORD imageFontAddress);

	// 设置字体颜色
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD graphics);

	// 从指定路径加载图像文件
	// isnewAddress存放了这个图像文件是否已经存在
	PSharedImageRef GetSharedImage(DWORD isnewAddress, PString variant, PString filename);

	// 将sharedImageRef转换为Image*返回
	PImage SharedImageRefToImage(PSharedImageRef imageRef);

	// 释放图像文件资源
	void FreeImage(PSharedImageRef imageRef);

	// 在指定位置绘制字体
	void DrawString(DWORD x, DWORD y, PString str, DWORD graphics);

	// 在指定位置绘制图片
	void DrawImage(DWORD x, DWORD y, PImage image, DWORD graphics);

	// 在指定位置绘制一条线
	void DrawLine(int startx, int starty, int endx, int endy, DWORD graphics);

	// 绘制空心矩形
	void DrawRect(int x, int y, int width, int height, DWORD graphics);

	// 绘制实心矩形
	void FillRect(int x, int y, int width, int height, DWORD graphics);

	// 绘制Edit的黄色输入框背景
	void DrawTextBox(DWORD edit, DWORD graphics);
}