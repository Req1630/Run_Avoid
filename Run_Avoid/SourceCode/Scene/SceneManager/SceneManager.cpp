#include "SceneManager.h"

void clsSceneManager::Update()
{
	m_pScene.top()->Updata();
}
void clsSceneManager::Draw( HDC hScreenDC, HDC hMemDC )
{
	m_pScene.top()->Draw( hScreenDC, hMemDC );
}
void clsSceneManager::Push( std::shared_ptr<clsSceneBase> pScenebase )
{
	m_pScene.emplace( pScenebase );
}
void clsSceneManager::Change( std::shared_ptr<clsSceneBase> pScenebase )
{
	clsSceneManager::Pop();
	clsSceneManager::Push( pScenebase );
}
void clsSceneManager::Pop()
{
	m_pScene.pop();
}
void clsSceneManager::Release()
{
	const int STACK_SIZE = m_pScene.size();
	for( int i = 0; i < STACK_SIZE; i++ ){
		m_pScene.pop();
	}
}