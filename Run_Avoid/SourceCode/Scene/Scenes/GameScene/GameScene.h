#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "..\..\SceneBase\SceneBase.h"

#include "..\..\..\Game\Map\Map.h"
#include "..\..\..\Game\Player\Player.h"

class clsGameScene : public clsSceneBase
{
public:
	clsGameScene( std::shared_ptr<clsSceneManager> &sceneManager );
	~clsGameScene();

	void Updata() override;
	void Draw( HDC hScreenDC, HDC hMemDC ) override;

	std::unique_ptr<CMap>		m_pMap;
	std::unique_ptr<CPlayer>	m_pPlayer;
};

#endif // #ifndef GAME_SCENE_H.