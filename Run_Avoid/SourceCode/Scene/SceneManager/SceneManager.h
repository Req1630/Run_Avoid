#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <stack>
#include <memory>

#include "..\SceneBase\SceneBase.h"

class clsSceneBase;

class clsSceneManager
{
public:
	clsSceneManager()
	{
	};
	~clsSceneManager()
	{
	};
	void Update();
	void Draw( HDC hScreenDC, HDC hMemDC );

	void Push( std::shared_ptr<clsSceneBase> pScenebase );
	void Change( std::shared_ptr<clsSceneBase> pScenebase );
	void Pop();
	void Release();

private:
	std::stack<std::shared_ptr<clsSceneBase>> m_pScene;
};

#endif // #ifndef SCENE_MANAGER_H.