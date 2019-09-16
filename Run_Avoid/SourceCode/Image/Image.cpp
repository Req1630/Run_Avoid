#include "Image.h"

bool CImage::LoadBmp( HBITMAP *hBmp, const char* filename )
{
	//�w�i�̓ǂݍ���.
	*hBmp = ( HBITMAP ) LoadImage (
		NULL,				//�C���X�^���X�ԍ�(�ȗ�).
		filename,			//�t�@�C����.
		IMAGE_BITMAP,		//�r�b�g�}�b�v�`��.
		0, 0,				//�ǂݍ��މ摜��x, y���W.
		LR_LOADFROMFILE );	//�t�@�C������ǂݍ���.

	if ( *hBmp == NULL ) {
		MessageBox ( NULL,
			"�摜�t�@�C���̓ǂݍ��ݎ��s",
			filename, MB_OK );
		return false;
	}
	return true;
}

//���ߕ\��.
void CImage::TrnsBlt(
	HDC hdc,		//DC.
	int x, int y,	//�\����x, y.
	int w, int h,	//�\����, ����.
	HDC hMemDC,		//������DC.
	int bx, int by )//���摜x, y���W.
{
	TransparentBlt (
		hdc,		//�\����DC.
		x, y,		//�\����x, y���W.
		w, h,		//�\�����镝, ����.
		hMemDC,		//������DC.
		bx, by,		//���摜x, y���W.
		w, h,		//���摜��, ����.
		RGB ( 0x00, 0xFF, 0x00 ));	//���ߐF(��).
}

//�������\��.
void CImage::ABlend ( HDC hDctDc,//�\����DC.
	int iDx, int iDy,	//�\����@x, y���W.
	int iw, int ih,		//�\�����A����.
	HDC hSrcDC,			//�ǂݍ��݌�DC.
	int iSx, int iSy,	//�ǂݍ��݌� x, y���W.
	int iAlpha )		//���ߒl(�A���t�@�l).
{
	//���ߍ\����.
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

void CImage::BitsBlt ( HDC hdc,	//�\��DC.
	int iDx, int iDy,		//�\����x, y���W.
	int iw, int ih,			//�\�����鍂��.
	HDC hMemDC,				//�o�b�N�o�b�t�@(�X���b�h���ō쐬).
	int bx, int by )		//���摜��x. y���W.
{
	BitBlt ( hdc,		//�f�o�C�X�R���e�L�X�g.
		iDx,  iDy,				//�\���ʒux, y.
		iw, ih,		//�摜�̕�,����.
		hMemDC,	//������DC.
		bx, by,				//���摜��x, y �摜�̂ǂ�����ǂ���؂��邩.
		SRCCOPY );
}