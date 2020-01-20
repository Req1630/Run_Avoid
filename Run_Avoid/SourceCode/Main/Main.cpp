#include "main.h"
#include "..\Global.h"
#include "..\Frame\Frame.h"
#include "..\Scene\SceneManager\SceneManager.h"
#include "..\Scene\Scenes\GameScene\GameScene.h"

//ｽﾚｯﾄﾞ関数.
DWORD WINAPI ThreadFunc( LPVOID vdParam )
{
	//変数宣言.
	GameWindow *gameWnd;//ｹﾞｰﾑｳｨﾝﾄﾞｳ構造体.
	//ｹﾞｰﾑｳｨﾝﾄﾞｳ構造体を取得.
	gameWnd = (GameWindow*)vdParam;//先頭ｱﾄﾞﾚｽをｷｬｽﾄして移す.

	HDC hMemDC;	//ﾒﾓﾘﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ.

	// フレームクラス.
	std::unique_ptr<CFrame> pFrame = std::make_unique<CFrame>();
	std::shared_ptr<clsSceneManager> pSceneManager =  std::make_shared<clsSceneManager>();
	pSceneManager->Push( std::make_shared<clsGameScene>(pSceneManager) );

	//------------------------------------------------
	//	起動処理[WM_CREATE].
	//------------------------------------------------

	//ﾒﾓﾘDCの作成.
	hMemDC = CreateCompatibleDC( nullptr );

	//ｳｨﾝﾄﾞｳが閉じられるまで無限ﾙｰﾌﾟ.
	while( !gameWnd->isWndClose )
	{
		pFrame->Init();

		//------------------------------------------------
		//	ｹﾞｰﾑ処理[WM_TIMER].
		//------------------------------------------------
		pSceneManager->Update();

		//------------------------------------------------
		//	描画処理[WM_PAINT].
		//------------------------------------------------
		pSceneManager->Draw( gameWnd->hScreenDC, hMemDC );

		pFrame->Draw( gameWnd->hScreenDC );
		pFrame->Update( gameWnd->hWnd );
	}

	//------------------------------------------------
	//	解放処理[WM_DESTROY].
	//------------------------------------------------
	pSceneManager->Release();

	pSceneManager.~shared_ptr();
	pFrame.~unique_ptr();

	//ﾒﾓﾘDCの解放.
	DeleteDC( hMemDC );

	// スレッド終了通知.
	ExitThread(0);

	return TRUE;
}

//ｳｨﾝﾄﾞｳ関数.
LRESULT CALLBACK WindowProc(
	HWND hWnd,		//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙ.
	UINT uMsg,		//ﾒｯｾｰｼﾞ.
	WPARAM wParam,	//ﾒｯｾｰｼﾞに対する情報.
	LPARAM lParam )	//ﾒｯｾｰｼﾞに対する情報.
{
	HDC hdc;	//ﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ.

	PAINTSTRUCT ps;//描画構造体.

	//-------------------------------------
	//	ｽﾚｯﾄﾞ関連.
	//-------------------------------------
	static GameWindow gameWnd;//ｹﾞｰﾑｳｨﾝﾄﾞｳ構造体.
	static HANDLE th;
	DWORD dwID;		//ｽﾚｯﾄﾞID.
	HBITMAP hBmp;	//ﾋﾞｯﾄﾏｯﾌﾟﾊﾝﾄﾞﾙ.

	//ﾒｯｾｰｼﾞ別の処理.
	switch( uMsg ){
	case WM_DESTROY://ｳｨﾝﾄﾞｳが破棄された時.

		//ｱﾌﾟﾘｹｰｼｮﾝの終了をWindowsに通知する.
		PostQuitMessage(0);
		return 0;

	case WM_CREATE:	//ｳｨﾝﾄﾞｳが生成された時.

		//------------------------------------
		//	ｽﾚｯﾄﾞの設定.
		//------------------------------------
		//ｽﾚｯﾄﾞに渡す値を設定.
		gameWnd.hWnd = hWnd;	//ｳｨﾝﾄﾞｳﾊﾝﾄﾞﾙ.
		gameWnd.size.cx = WND_W;//ｳｨﾝﾄﾞｳ幅.
		gameWnd.size.cy = WND_H;//ｳｨﾝﾄﾞｳ高さ.
		gameWnd.dwFPS = FPS;	//FPS値(基準).

		//HDCの作成.
		hdc = GetDC( hWnd );//DC(ﾃﾞﾊﾞｲｽｺﾝﾃｷｽﾄ)を取得.

		//ﾋﾞｯﾄﾏｯﾌﾟﾊﾝﾄﾞﾙを作成.
		hBmp = CreateCompatibleBitmap(
			hdc,
			gameWnd.size.cx,
			gameWnd.size.cy );

		//DCと互換性のあるDCを作成.
		gameWnd.hScreenDC = CreateCompatibleDC(hdc);

		//hScreenDCをﾋﾞｯﾄﾏｯﾌﾟ用として定義.
		SelectObject( gameWnd.hScreenDC, hBmp );

		//不要になったDCを解放.
		ReleaseDC( hWnd, hdc );

		//ｽﾚｯﾄﾞの作成と実行.
		th = CreateThread(
			nullptr,//ﾊﾝﾄﾞﾙを他のﾌﾟﾛｾｽと共有する場合は指定.
			0,					//ｽﾀｯｸｻｲｽﾞ(ﾃﾞﾌｫﾙﾄ:0).
			ThreadFunc,			//ｽﾚｯﾄﾞ関数名.
			(LPVOID)&gameWnd,	//ｽﾚｯﾄﾞに渡す構造体.
			0,					//0:作成と同時に実行.
			&dwID);				//(out)ｽﾚｯﾄﾞID.

		return 0;

	case WM_PAINT:	//ｳｨﾝﾄﾞｳが更新された時.
					//描画開始.
		hdc = BeginPaint( hWnd, &ps );

		BitBlt(
			hdc,	//表示DC.
			0, 0,	//表示先x,y座標.
			gameWnd.size.cx,//表示する幅.
			gameWnd.size.cy,//表示する高さ.
			gameWnd.hScreenDC,//ﾊﾞｯｸﾊﾞｯﾌｧ(ｽﾚｯﾄﾞ内で作成).
			0, 0,	//元画像のx,y座標.
			SRCCOPY);//ｺﾋﾟｰする.

		//描画終了.
		EndPaint( hWnd, &ps );
		return 0;
	case WM_KEYDOWN://ｷｰが押された.
		//ｷｰ別の処理.
		switch( wParam ){
		case VK_ESCAPE:	//Esc.
			if( MessageBox( nullptr,
				"ｹﾞｰﾑを終了しますか？","警告",
				MB_YESNO ) == IDYES )
			{
				gameWnd.isWndClose = TRUE;
			}
			break;
		}
		if( !gameWnd.isWndClose ) break;
	case WM_CLOSE:
		DWORD result;
		gameWnd.isWndClose = TRUE;
		while(1){
            //スレッドが終わったかチェック
            GetExitCodeThread(th,&result);
            //終わったらハンドルを閉じる。
            if(STILL_ACTIVE!=result){
                //closehandleで閉じる。
                CloseHandle(th);
                //ループを抜ける。
                break;
            }
        }
		//ｳｨﾝﾄﾞｳを破棄する.
		DestroyWindow ( hWnd );
		return 0;
	}

	//ﾒｲﾝに返す情報.
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

//メイン関数.
int WINAPI WinMain(
	HINSTANCE hInstance,	//インスタンス番号(ｳｨﾝﾄﾞｳの番号).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdshow )
{
#ifdef _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif	// #ifdef _DEBUG.
	WNDCLASS wc;	//ウィンドウクラス構造体.
	HWND hWnd;		//ウィンドウハンドル.
	MSG msg;		//メッセージ.
					// アイコンの作成
//		HICON res_icon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );

	//------------------------------------------------
	//	複数CPUに対応させる▼.
	//------------------------------------------------
	DWORD	ProcessAffinitMask;	//CPUを指定.
	HANDLE	hProcess;	//ﾌﾟﾛｾｽﾊﾝﾄﾞﾙ.
	DWORD	errnum;		//ｴﾗｰNo.
	BOOL	ret;		//関数復帰値.



						//自身のﾌﾟﾛｾｽのﾊﾝﾄﾞﾙを取得.
	hProcess = GetCurrentProcess();

	//自身を動作させるCPUを指定する.
	ProcessAffinitMask = 1;	//CPU0を使う(2進数で指定する).
	ret = SetProcessAffinityMask(
		hProcess,
		ProcessAffinitMask );
	if( ret == FALSE ){
		errnum = GetLastError();	//ｴﾗｰ情報を取得.
		return 0;
	}

	//------------------------------------------------
	//	複数CPUに対応させる▲.
	//------------------------------------------------

	//ウィンドウクラスの登録.
	wc.style = CS_HREDRAW | CS_VREDRAW;	//スタイルの登録.
	wc.lpfnWndProc = WindowProc;		//ウィンドウ関数の登録(DefWindowProc:ﾃﾞﾌｫﾙﾄ).
	wc.hInstance = hInstance;			//インスタンス番号の登録.
	wc.hIcon = nullptr;					//アイコンの登録.
	wc.hCursor = nullptr;					//カーソルの登録.
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//背景色.
	wc.lpszMenuName = nullptr;				//メニューの登録.
	wc.cbClsExtra = 0;					//拡張用メンバ(使わないので０で固定).
	wc.cbWndExtra = 0;					//拡張用メンバ(使わないので０で固定).
	wc.lpszClassName = APP_NAME;		//アプリケーション名.

										//ウィンドウクラスをWindowsに登録.
	if ( !RegisterClass ( &wc ) ){
		MessageBox ( nullptr, "ウィドウクラスの登録に失敗",
			"ｴﾗｰ", MB_OK );
		return 0;
	}

	//ウィンドウ領域の調整.
	RECT rect;		//短形構造体.
	RECT deskrect;

	rect.left	= 0;	//左.
	rect.top	= 0;	//上.
	rect.right	= WND_W;//右.
	rect.bottom = WND_H;//下.

	// WS_OVERLAPPEDWINDOW, WS_POPUP.


	if ( !AdjustWindowRect (
		&rect,	//(in)画面サイズが入った短形構造体、(out)計算結果.
		(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME|WS_MAXIMIZEBOX)),//ウィンドウスタイル.
		FALSE ))	//メニューを持つかどうか.
	{
		MessageBox (nullptr,
			"ウィンドウ領域の調整に失敗",
			"エラー", MB_OK );
		return 0;
	}
	SystemParametersInfo(SPI_GETWORKAREA, 0, &deskrect, 0);


	//ｳｨﾝﾄﾞｳの作成.
	hWnd = CreateWindow(
		APP_NAME,	//ｱﾌﾟﾘｹｰｼｮﾝ名(構造体と同じ名前にする).
		WND_TITLE,	//ｳｨﾝﾄﾞｳﾀｲﾄﾙ.
		(WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME|WS_MAXIMIZEBOX)),	//ｳｨﾝﾄﾞｳ種類.
		(((deskrect.right - deskrect.left) - (rect.right - rect.left)) / 2 + deskrect.left), 
		(((deskrect.bottom - deskrect.top) - (rect.bottom - rect.top)) / 2 + deskrect.top),		//表示位置x,y.
		rect.right - rect.left,	//ウィンドウの幅.
		rect.bottom - rect.top,	//ｳｨﾝﾄﾞｳの高さ.
		nullptr,		//親ｳｨﾝﾄﾞｳのﾊﾝﾄﾞﾙ.
		nullptr,		//ﾒﾆｭｰの設定.
		hInstance,	//ｲﾝｽﾀﾝｽ番号.
		nullptr);//ｳｨﾝﾄﾞｳ作成時に発生するｲﾍﾞﾝﾄに渡すﾃﾞｰﾀ.

	if( hWnd == nullptr ){
		MessageBox( nullptr, "ｳｨﾝﾄﾞｳの作成に失敗",
			"ｴﾗｰ", MB_OK );
		return 0;
	}

	//ウィンドウの表示.
	ShowWindow ( hWnd, SW_SHOW ); 
	//SW_SHOW:表示、SW_HIDE:非表示.

	//メッセージループ.
	while ( GetMessage ( &msg, nullptr, 0, 0 ) > 0 ){

		//ウィンドウ関数にメッセージを送る,
		DispatchMessage ( &msg );
	}

	return 0;
}
