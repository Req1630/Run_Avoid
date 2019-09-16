#ifndef IMAGE_H
#define IMAGE_H

#include "..\Global.h"
#include "..\SingletonBase\SingletonBase.h"

//�w��F�𓧉߂��ĕ`�悷�鏈���ŕK�v.
#pragma comment ( lib, "msimg32.lib" )

class CImage : public CSingletonBase<CImage>
{
public:

	static bool LoadBmp( HBITMAP *hBmp, const char* filename );

	//���ߕ\��.
	static void TrnsBlt( HDC hdc,		//DC.
		int x, int y,			//�\����x, y.
		int w, int h,			//�\����, ����.
		HDC hMemDC,				//������DC.
		int bx, int by );		//���摜x, y���W.

	//�������\��.
	static void ABlend ( HDC hdc,		//�\����DC.
		int iDx, int iDy,		//�\����@x, y���W.
		int iw, int ih,			//�\�����A����.
		HDC hMemDC,				//�ǂݍ��݌�DC.
		int iSx, int iSy,		//�ǂݍ��݌� x, y���W.
		int iAlpha );			//���ߒl(�A���t�@�l).

	static void BitsBlt ( HDC hdc,		//�\��DC.
		int x, int y,			//�\����x, y���W.
		int w, int h,			//�\�����鍂��.
		HDC hMemDC,				//�o�b�N�o�b�t�@(�X���b�h���ō쐬).
		int bx, int by );		//���摜��x. y���W.
};

#endif	// #ifndef IMAGE_H.