#include "GameScene.h"

clsGameScene::clsGameScene( std::shared_ptr<clsSceneManager> &sceneManager )
	: clsSceneBase	( sceneManager )
	, m_pMap		( std::make_unique<CMap>() )
	, m_pPlayer		( std::make_unique<CPlayer>() )
{
}
clsGameScene::~clsGameScene()
{}

void clsGameScene::Updata()
{
	m_pMap->Update();
	m_pPlayer->Update();
}

void clsGameScene::Draw( HDC hScreenDC, HDC hMemDC )
{
	m_pMap->Draw( hScreenDC, hMemDC );
	m_pPlayer->Draw( hScreenDC, hMemDC ); 
}