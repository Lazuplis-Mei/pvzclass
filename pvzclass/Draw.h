#pragma once
#include "PVZ.h"

// ����DrawUITopEvent���ʹ��
namespace Draw
{
	typedef DWORD PString;
	typedef DWORD PSharedImageRef;
	typedef DWORD PImage;
	extern BYTE color[16];

	// ���ַ�����ת��Ϊ�ַ���
	PString ToString(const char* str);

	// ���ַ���ת��Ϊ�ַ�����
	char* ToChar(PString str);

	// �������壬���ں���������⴦���������ʵ���ϵ��õ��Ǽ����ַ�������
	void StringWidth(PString str, DWORD imageFontAddress);

	// ����������ɫ
	void SetColor(DWORD r, DWORD g, DWORD b, DWORD graphics);

	// ��ָ��·������ͼ���ļ�
	// isnewAddress��������ͼ���ļ��Ƿ��Ѿ�����
	PSharedImageRef GetSharedImage(DWORD isnewAddress, PString variant, PString filename);

	// ��sharedImageRefת��ΪImage*����
	PImage SharedImageRefToImage(PSharedImageRef imageRef);

	// �ͷ�ͼ���ļ���Դ
	void FreeImage(PSharedImageRef imageRef);

	// ��ָ��λ�û�������
	void DrawString(DWORD x, DWORD y, PString str, DWORD graphics);

	// ��ָ��λ�û���ͼƬ
	void DrawImage(DWORD x, DWORD y, PImage image, DWORD graphics);

	// ��ָ��λ�û���һ����
	void DrawLine(int startx, int starty, int endx, int endy, DWORD graphics);

	// ���ƿ��ľ���
	void DrawRect(int x, int y, int width, int height, DWORD graphics);

	// ����ʵ�ľ���
	void FillRect(int x, int y, int width, int height, DWORD graphics);

	// ����Edit�Ļ�ɫ����򱳾�
	void DrawTextBox(DWORD edit, DWORD graphics);
}