#ifndef MAIN_H
#define MAIN_H
#include <Windows.h>

//�����Đ�,����ѽگ�ނŎg�p����.
#pragma comment( lib, "winmm.lib" )

//�\���̐錾.
typedef struct _GameWindow{
	HWND	hWnd;		//����޳�����.
	HDC		hScreenDC;	//�ޯ��ޯ̧.
	SIZE	size;		//����.
	DWORD	dwFPS;		//FPS(Frame Per Second:�ڰ�/�b).
	BOOL	isWndClose;
} GameWindow;

#endif	// #ifndef MAIN_H.