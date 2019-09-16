#include "..\..\Global.h"
#include "..\..\Image\Image.h"
#include "Map.h"

#include <fstream>
#include <iostream>

CMap::CMap()
	: m_hMapBmp			( nullptr )
	, m_iMapChip		( nullptr )
	, m_iGoalMapChip	( nullptr )
	, m_iBufferMap		( nullptr )
	, m_iScrollPosX		( 0 )
	, m_RunDistance		( 0 )
	, m_iGoalCount		( 0 )
{
	MapLoad();
	GoalMalLoad();
	// マップ画像の読み込み.
	CImage::LoadBmp( &m_hMapBmp, "Data\\BMP\\mapdata.bmp");

	m_iBufferMap = new int[MAP_SIZE_Y];
}

CMap::~CMap()
{
	// マップ画像の解放.
	DeleteObject( m_hMapBmp );
	delete[] m_iBufferMap;
	// 動的確保したマップの解放.
	for( int i = MAP_SIZE_X-1; i >= 0; i-- ){
		delete[] m_iMapChip[i];
	}
	delete[] m_iMapChip;
	// 動的確保したマップの解放.
	for( int i = GOAL_MAP_SIZE_X-1; i >= 0; i-- ){
		delete[] m_iGoalMapChip[i];
	}
	delete[] m_iGoalMapChip;
}

void CMap::Update()
{
	if( m_RunDistance <= GOAL_DISTANCE ){
		Scroll();
	} else {
		GoalScroll();
	}
}

void CMap::Draw( HDC hScreenDC, HDC hMemDC )
{	
	for( int y = 0; y < MAP_SIZE_Y; y++ ){
		for( int x = 0; x < MAP_SIZE_X; x++ ){
			SelectObject( hMemDC, m_hMapBmp );
			CImage::BitsBlt(
				hScreenDC,
				-m_iScrollPosX + x * MAP_IMAGE_SIZE, 
				y * MAP_IMAGE_SIZE,
				MAP_IMAGE_SIZE, 
				MAP_IMAGE_SIZE,
				hMemDC,
				MAP_IMAGE_SIZE * m_iMapChip[x][y], 0 );
		}
	}
}

void CMap::Scroll()
{

	if( m_iScrollPosX < MAP_IMAGE_SIZE ){
		m_iScrollPosX += MAP_SCROLL_SPD;
	} else {
		m_iScrollPosX = 0;
		//マップの x[0](最初) を　x[MAP_W - 1](最後)に入れ替える.
		//------------------------------------------------------------
		memcpy_s ( m_iBufferMap, sizeof(m_iBufferMap)*MAP_SIZE_Y, 
			m_iMapChip[0], sizeof(m_iMapChip[0])*MAP_SIZE_Y );
		for ( int x = 0; x < MAP_SIZE_X - 1; x++ ){
			memcpy_s ( m_iMapChip[x], sizeof(m_iMapChip[x])*MAP_SIZE_Y, 
				m_iMapChip[x+1], sizeof(m_iMapChip[x+1])*MAP_SIZE_Y );
		}
		memcpy_s ( m_iMapChip[MAP_SIZE_X-1], sizeof(m_iMapChip[MAP_SIZE_X-1])*MAP_SIZE_Y,
			m_iBufferMap, sizeof(m_iBufferMap)*MAP_SIZE_Y );
		//------------------------------------------------------------
		m_RunDistance++;
	}
}

// マップ逆スクロール.
void CMap::BackScroll()
{
	if ( m_iScrollPosX > 0 ){
		m_iScrollPosX -= MAP_SCROLL_SPD;
	} else {
		m_iScrollPosX = MAP_IMAGE_SIZE;
		//マップの x[0](最初) を　x[MAP_W - 1](最後)に入れ替える.
		//------------------------------------------------------------
		memcpy_s ( m_iBufferMap, sizeof(m_iBufferMap)*MAP_SIZE_Y, 
			m_iMapChip[MAP_SIZE_X - 1], sizeof(m_iMapChip[MAP_SIZE_X - 1])*MAP_SIZE_Y );
		for ( int x = MAP_SIZE_X - 1; x > 0; x-- ){
			memcpy_s ( m_iMapChip[x], sizeof(m_iMapChip[x])*MAP_SIZE_Y, 
				m_iMapChip[x - 1], sizeof(m_iMapChip[x - 1])*MAP_SIZE_Y );
		}
		memcpy_s ( m_iMapChip[0], sizeof(m_iMapChip[0])*MAP_SIZE_Y,
			m_iBufferMap, sizeof(m_iBufferMap)*MAP_SIZE_Y );
		//------------------------------------------------------------
	}
}

// ゴールマップスクロール関数.
void CMap::GoalScroll()
{
	if( m_iGoalCount >= GOAL_MAP_SIZE_X ) return;

	if( m_iScrollPosX < MAP_IMAGE_SIZE ){
		m_iScrollPosX += MAP_SCROLL_SPD;
	} else {
		m_iScrollPosX = 0;
		//マップの x[0](最初) を　x[MAP_W - 1](最後)に入れ替える.
		//------------------------------------------------------------
		memcpy_s ( m_iBufferMap, sizeof(m_iBufferMap)*MAP_SIZE_Y, 
			m_iMapChip[0], sizeof(m_iMapChip[0])*MAP_SIZE_Y );
		for ( int x = 0; x < MAP_SIZE_X - 1; x++ ){
			memcpy_s ( m_iMapChip[x], sizeof(m_iMapChip[x])*MAP_SIZE_Y, 
				m_iMapChip[x+1], sizeof(m_iMapChip[x+1])*MAP_SIZE_Y );
		}
		memcpy_s ( m_iMapChip[MAP_SIZE_X-1], sizeof(m_iMapChip[MAP_SIZE_X-1])*MAP_SIZE_Y,
			m_iGoalMapChip[m_iGoalCount], sizeof(m_iGoalMapChip)*MAP_SIZE_Y );
		//------------------------------------------------------------
		m_iGoalCount++;
	}
}

void CMap::MapLoad()
{
	using namespace std;

	// マップの動的確保.
	m_iMapChip = new int*[MAP_SIZE_X];
	for( int i = 0; i < MAP_SIZE_X; i++ ){
		m_iMapChip[i] = new int[MAP_SIZE_Y];
	}

	ifstream ifs(MAP_DATA_PATH);
	char* sMap = new char[MAP_SIZE_X+1];
	int y = 0;
	char buf[2] = "";
	while (ifs.getline(sMap, MAP_SIZE_X+1))
	{
		if( y >= MAP_SIZE_Y )	break;	
		for( int x = 0; x < MAP_SIZE_X; x++ ){
			buf[0] = sMap[x];
			m_iMapChip[x][y] = atoi( buf );
		}
		y++;
	}
	delete[] sMap;
}

// ゴールマップの読み込み.
void CMap::GoalMalLoad()
{
	using namespace std;

	// マップの動的確保.
	m_iGoalMapChip = new int*[GOAL_MAP_SIZE_X];
	for( int i = 0; i < GOAL_MAP_SIZE_X; i++ ){
		m_iGoalMapChip[i] = new int[MAP_SIZE_Y];
	}

	ifstream ifs(GOAL_MAP_DATE_PATH);
	char* sMap = new char[GOAL_MAP_SIZE_X+1];
	int y = 0;
	char buf[2] = "";
	while (ifs.getline(sMap, GOAL_MAP_SIZE_X+1))
	{
		if( y >= MAP_SIZE_Y )	break;	
		for( int x = 0; x < GOAL_MAP_SIZE_X; x++ ){
			buf[0] = sMap[x];
			m_iGoalMapChip[x][y] = atoi( buf );
		}
		y++;
	}
	delete[] sMap;
}