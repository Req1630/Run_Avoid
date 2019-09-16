#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "..\..\Global.h"

#include "..\SceneManager\SceneManager.h"


class clsSceneManager;

class clsSceneBase
{
public:
	clsSceneBase( std::shared_ptr<clsSceneManager> &sceneManager );
	virtual ~clsSceneBase(){};

	virtual void Updata() = 0;
	virtual void Draw( HDC hScreenDC, HDC hMemDC ) = 0;

protected:
	std::shared_ptr<clsSceneManager> m_SceneManager;
};

#endif // #ifndef SCENE_BASE_H.