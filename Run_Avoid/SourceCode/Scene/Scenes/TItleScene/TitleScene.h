#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "..\..\SceneBase\SceneBase.h"

class clsTitleScene : public clsSceneBase
{
public:
	clsTitleScene( std::shared_ptr<clsSceneManager> &sceneManager );
	~clsTitleScene();

	void Updata() override;
	void Draw( HDC hScreenDC, HDC hMemDC ) override;
};

#endif // #ifndef TITLE_SCENE_H.