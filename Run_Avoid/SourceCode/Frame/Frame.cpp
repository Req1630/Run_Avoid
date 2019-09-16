#include "Frame.h"

DWORD CFrame::s_dwFrames = 0;

CFrame::CFrame()
	: m_dwBeforeTime	( 0 )
	, m_sFPS			( "" )
	, m_dwNowTime		( 0 )
	, m_dwProgress		( 0 )
	, m_dwIdealTime		( 0 )
{
	m_dwBeforeTime = timeGetTime();//���݂̎��Ԃ��擾.
}

CFrame::~CFrame()
{
}

void CFrame::Init()
{
	m_dwNowTime = 0;	//���݂̎���.
	m_dwProgress = 0;	//�o�ߎ���.
	m_dwIdealTime = 0;//���z����.

	m_dwNowTime = timeGetTime();//���݂̎��Ԃ��擾.

	m_dwProgress = m_dwNowTime - m_dwBeforeTime;//�o�ߎ���.

	//���z���Ԃ̎Z�o.
	//(���݂��ڰѐ��~(1000��FPS�l)).
	m_dwIdealTime = 
		(DWORD)(s_dwFrames*(1000.0F/FPS));
}

void CFrame::Update( HWND hWnd )
{
	//�`��̎��ԑ҂�.
	if( m_dwIdealTime > m_dwProgress ){
		Sleep( m_dwIdealTime - m_dwProgress );//���ԑ҂�.
	}

	//�ĕ`��.
	InvalidateRect( hWnd, nullptr, FALSE );

	//�P�b�o��.
	if( m_dwProgress >= 1000 ){
		
		wsprintf( m_sFPS, "FPS[%03d]", s_dwFrames );
		m_dwBeforeTime = m_dwNowTime;//���݂̎��ԂɍX�V.
		s_dwFrames = 0;
	}
	s_dwFrames++;	//�ڰѐ�UP.
}

void CFrame::Draw( HDC hDC )
{
#ifdef _DEBUG
	//FPS�̕\��.
	TextOut( hDC, WND_W-100, 0, m_sFPS, lstrlen(m_sFPS) );
#endif	// #ifdef _DEBUG.
}