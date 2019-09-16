#include "Player.h"

CPlayer::CPlayer()
{
	m_vPosition.x = 0;
	m_vPosition.y = 0;
	CImage::LoadBmp( &m_hCharaBmp, "Data\\BMP\\chara.bmp" );
}

CPlayer::~CPlayer()
{
	DeleteObject( m_hCharaBmp );
}

void CPlayer::Update()
{}

void CPlayer::Draw( HDC hScreenDC, HDC hMemDC )
{
	SelectObject( hMemDC, m_hCharaBmp );
	CImage::TrnsBlt(
		hScreenDC,
		m_vPosition.x,
		m_vPosition.y,
		PLAYER_IMAGE_SIZE, 
		PLAYER_IMAGE_SIZE,
		hMemDC,
		PLAYER_IMAGE_SIZE * m_Anim.Pattern,
		PLAYER_IMAGE_SIZE );
}