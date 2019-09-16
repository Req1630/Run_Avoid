#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include "..\..\Image\Image.h"

struct Vecter2D
{
	int x;	
	int y;
};

// アニメーション情報構造体.
struct Animation
{
	int Count;		// アニメーションカウント.
	int Pattern;	// アニメーションパターン.
};

class CCharacterBase
{
public:
	CCharacterBase();
	~CCharacterBase();

	virtual void Update() = 0;
	virtual void Draw( HDC hScreenDC, HDC hMemDC ) = 0;

protected:
	HBITMAP		m_hCharaBmp;	// キャラクタ用画像.

	Vecter2D	m_vPosition;	// 座標.
	bool		m_bisDead;		// 死亡フラグ.
	Animation	m_Anim;			// アニメーション情報.
	int			m_iHitPpint;	// 体力.
};

#endif	// #ifndef CHARACTER_BASE_H.