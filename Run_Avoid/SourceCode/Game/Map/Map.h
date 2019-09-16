#ifndef MAP_H
#define MAP_H

class CMap
{
	const int MAP_IMAGE_SIZE	= 48;	// マップの画像サイズ.
	const int MAP_SIZE_X		= 17;	// マップチップのサイズ.
	const int MAP_SIZE_Y		= 10;	// マップチップのサイズ.
	const int GOAL_MAP_SIZE_X	= 9;	// ゴール用マップチップのサイズ.
	const int MAP_SCROLL_SPD	= 4;	// マップスクロールの速さ.

	const int GOAL_DISTANCE		= 100;	// ゴールまでの距離.

	const char* MAP_DATA_PATH		= "Data\\MAP\\mapchipdata.txt";
	const char* GOAL_MAP_DATE_PATH	= "Data\\MAP\\mapchipgoaldata.txt";
public:
	CMap();
	~CMap();

	// 更新関数.
	void Update();
	// 描画関数.
	void Draw( HDC hScreenDC, HDC hMemDC );

private:
	// マップスクロール関数.
	void Scroll();
	// マップ逆スクロール.
	void BackScroll();
	// ゴールマップスクロール関数.
	void GoalScroll();
	// マップの読み込み.
	void MapLoad();	
	// ゴールマップの読み込み.
	void GoalMalLoad();

private:
	HBITMAP	m_hMapBmp;		// マップ画像.
	int**	m_iMapChip;		// マップ情報.
	int**	m_iGoalMapChip;	// ゴールマップ情報.

	int*	m_iBufferMap;	// スクロール用

	int		m_iScrollPosX;	// スクロール座標.
	int		m_RunDistance;	// 走っている距離.
	int		m_iGoalCount;	// ゴールカウント.

};

#endif	// #ifndef MAP_H.