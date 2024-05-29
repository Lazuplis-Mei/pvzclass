#pragma once
#include "PVZ.h"
#include <vector>
#include <algorithm>

// ����DrawUITopEvent���ʹ��
namespace Draw
{
	// ���ַ�����ת��Ϊ�ַ���������Ϊ�ַ�����ĵ�ַ������ֵΪ�ַ����ĵ�ַ
	void ToString(DWORD fromAddress, DWORD toAddress);

	// �������壬���ں���������⴦���������ʵ���ϵ��õ��Ǽ����ַ�������
	void StringWidth(DWORD stringAddress, DWORD imageFontAddress);

	// ����������ɫ
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD colorAddress, DWORD graphics);

	// ��ָ��λ�û�������
	void DrawString(DWORD x, DWORD y, DWORD stringAddress, DWORD graphics);

	// ��ָ��λ�û���ͼƬ
	void DrawImage(DWORD x, DWORD y, DWORD imageAddress, DWORD graphics);
}