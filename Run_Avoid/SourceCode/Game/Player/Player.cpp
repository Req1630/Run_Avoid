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

		// �W�����v�r�b�g�𗧂Ă�.
		m_NowState |= static_cast<int>(enState::Jump);
		// �d�͂�����������.
		m_iGravity = 0;
	}
}

void CPlayer::JumpState()
{
	if(!(m_NowState & static_cast<int>(enState::Jump))) return;

	m_vPosition.y -= ( 16.0f - m_iGravity );

	m_iGravity += 1.0;
	//py �� P_Y��葽���Ȃ�����.
	if ( m_vPosition.y > PLAYER_INIT_POS_Y ){
		m_vPosition.y = PLAYER_INIT_POS_Y;				// �n�ʂ̍����ɍ��킹��.
		m_NowState ^= static_cast<int>(enState::Jump);	// �W�����v�r�b�g������.
	}
}

void CPlayer::SquatState()
{
	if(!(m_NowState & static_cast<int>(enState::Squat))) return;
}