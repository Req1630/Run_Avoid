#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include "..\..\Image\Image.h"

struct Vecter2D
{
	int x;	
	int y;
};

// �A�j���[�V�������\����.
struct Animation
{
	int Count;		// �A�j���[�V�����J�E���g.
	int Pattern;	// �A�j���[�V�����p�^�[��.
};

class CCharacterBase
{
public:
	CCharacterBase();
	~CCharacterBase();

	virtual void Update() = 0;
	virtual void Draw( HDC hScreenDC, HDC hMemDC ) = 0;

protected:
	HBITMAP		m_hCharaBmp;	// �L�����N�^�p�摜.

	Vecter2D	m_vPosition;	// ���W.
	bool		m_bisDead;		// ���S�t���O.
	Animation	m_Anim;			// �A�j���[�V�������.
	int			m_iHitPpint;	// �̗�.
};

#endif	// #ifndef CHARACTER_BASE_H.