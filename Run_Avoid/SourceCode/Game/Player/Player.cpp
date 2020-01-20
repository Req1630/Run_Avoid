#include "Player.h"

CPlayer::CPlayer()
	: m_NowState	( static_cast<int>(enState::None) )
	, m_iGravity	( 0 )
{
	m_vPosition.x = PLAYER_INIT_POS_X;
	m_vPosition.y = PLAYER_INIT_POS_Y;
	CImage::LoadBmp( &m_hCharaBmp, "Data\\BMP\\chara.bmp" );
}

CPlayer::~CPlayer()
{
	DeleteObject( m_hCharaBmp );
}

void CPlayer::Update()
{
	Control();
	JumpState();
}

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

void CPlayer::Control()
{
	if( GetAsyncKeyState( VK_UP ) & 0x8000 ){
		if(m_NowState & static_cast<int>(enState::Dead)) return;
		if(m_NowState & static_cast<int>(enState::Jump)) return;

		// ジャンプビットを立てる.
		m_NowState |= static_cast<int>(enState::Jump);
		// 重力を初期化する.
		m_iGravity = 0;
	}
}

void CPlayer::JumpState()
{
	if(!(m_NowState & static_cast<int>(enState::Jump))) return;

	m_vPosition.y -= ( 16.0f - m_iGravity );

	m_iGravity += 1.0;
	//py が P_Yより多くなったら.
	if ( m_vPosition.y > PLAYER_INIT_POS_Y ){
		m_vPosition.y = PLAYER_INIT_POS_Y;				// 地面の高さに合わせる.
		m_NowState ^= static_cast<int>(enState::Jump);	// ジャンプビットを下す.
	}
}

void CPlayer::SquatState()
{
	if(!(m_NowState & static_cast<int>(enState::Squat))) return;
}