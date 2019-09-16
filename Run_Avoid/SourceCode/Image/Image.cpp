#include "Image.h"

bool CImage::LoadBmp( HBITMAP *hBmp, const char* filename )
{
	//背景の読み込み.
	*hBmp = ( HBITMAP ) LoadImage (
		NULL,				//インスタンス番号(省略).
		filename,			//ファイル名.
		IMAGE_BITMAP,		//ビットマップ形式.
		0, 0,				//読み込む画像のx, y座標.
		LR_LOADFROMFILE );	//ファイルから読み込む.

	if ( *hBmp == NULL ) {
		MessageBox ( NULL,
			"画像ファイルの読み込み失敗",
			filename, MB_OK );
		return false;
	}
	return true;
}

//透過表示.
void CImage::TrnsBlt(
	HDC hdc,		//DC.
	int x, int y,	//表示先x, y.
	int w, int h,	//表示幅, 高さ.
	HDC hMemDC,		//メモリDC.
	int bx, int by )//元画像x, y座標.
{
	TransparentBlt (
		hdc,		//表示先DC.
		x, y,		//表示先x, y座標.
		w, h,		//表示する幅, 高さ.
		hMemDC,		//メモリDC.
		bx, by,		//元画像x, y座標.
		w, h,		//元画像幅, 高さ.
		RGB ( 0x00, 0xFF, 0x00 ));	//透過色(緑).
}

//半透明表示.
void CImage::ABlend ( HDC hDctDc,//表示先DC.
	int iDx, int iDy,	//表示先　x, y座標.
	int iw, int ih,		//表示幅、高さ.
	HDC hSrcDC,			//読み込み元DC.
	int iSx, int iSy,	//読み込み元 x, y座標.
	int iAlpha )		//透過値(アルファ値).
{
	//透過構造体.
	BLENDFUNCTION blendfunc = { AC_SRC_OVER, (BYTE)0, (BYTE)iAlpha, (BYTE)0 };

	AlphaBlend ( 
		hDctDc,
		iDx, iDy,
		iw, ih,
		hSrcDC,
		iSx, iSy,
		iw, ih,
		blendfunc );
}

void CImage::BitsBlt ( HDC hdc,	//表示DC.
	int iDx, int iDy,		//表示先x, y座標.
	int iw, int ih,			//表示する高さ.
	HDC hMemDC,				//バックバッファ(スレッド内で作成).
	int bx, int by )		//元画像のx. y座標.
{
	BitBlt ( hdc,		//デバイスコンテキスト.
		iDx,  iDy,				//表示位置x, y.
		iw, ih,		//画像の幅,高さ.
		hMemDC,	//メモリDC.
		bx, by,				//元画像のx, y 画像のどこからどこを切り取るか.
		SRCCOPY );
}