#ifndef IMAGE_H
#define IMAGE_H

#include "..\Global.h"
#include "..\SingletonBase\SingletonBase.h"

//指定色を透過して描画する処理で必要.
#pragma comment ( lib, "msimg32.lib" )

class CImage : public CSingletonBase<CImage>
{
public:

	static bool LoadBmp( HBITMAP *hBmp, const char* filename );

	//透過表示.
	static void TrnsBlt( HDC hdc,		//DC.
		int x, int y,			//表示先x, y.
		int w, int h,			//表示幅, 高さ.
		HDC hMemDC,				//メモリDC.
		int bx, int by );		//元画像x, y座標.

	//半透明表示.
	static void ABlend ( HDC hdc,		//表示先DC.
		int iDx, int iDy,		//表示先　x, y座標.
		int iw, int ih,			//表示幅、高さ.
		HDC hMemDC,				//読み込み元DC.
		int iSx, int iSy,		//読み込み元 x, y座標.
		int iAlpha );			//透過値(アルファ値).

	static void BitsBlt ( HDC hdc,		//表示DC.
		int x, int y,			//表示先x, y座標.
		int w, int h,			//表示する高さ.
		HDC hMemDC,				//バックバッファ(スレッド内で作成).
		int bx, int by );		//元画像のx. y座標.
};

#endif	// #ifndef IMAGE_H.