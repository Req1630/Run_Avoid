#ifndef FRAME_H
#define FRAME_H

#include "..\Global.h"

class CFrame
{
public:
	CFrame();
	~CFrame();

	void Init();
	void Update( HWND hWnd );
	void Draw( HDC hDC );

	DWORD GetFrameNum(){ return s_dwFrames; };

private:
	static DWORD s_dwFrames;		//�ڰѐ�.
	DWORD m_dwBeforeTime;	//�O�̎���.
	char m_sFPS[32];

	DWORD m_dwNowTime;	//���݂̎���.
	DWORD m_dwProgress;	//�o�ߎ���.
	DWORD m_dwIdealTime;//���z����.

};

#endif	// #ifndef FRAME_H.