#pragma once
#include "PVZ.h"
#include <vector>
#include <algorithm>

namespace Draw
{
	// �������壬���ں���������⴦���������ʵ���ϵ��õ��Ǽ����ַ�������
	void StringWidth(std::string *s, DWORD imageFontAddress);

	// ����������ɫ
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD graphics);

	// ��ָ��λ�û�������
	void DrawString(DWORD x, DWORD y, std::string *s, DWORD graphics);
}