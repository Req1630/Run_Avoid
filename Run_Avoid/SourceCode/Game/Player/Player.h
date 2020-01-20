#ifndef PLAYER_H
#define PLAYER_H

#include "..\CharacterBase\CharacterBase.h"

class CPlayer : public CCharacterBase
{
	const int PLAYER_IMAGE_SIZE = 48;	// プレイヤー画像サイズ.

	const int PLAYER_INIT_POS_X = WND_W/2 - PLAYER_IMAGE_SIZE/2;	// プレイヤー初期配置 x座標.
	const int PLAYER_INIT_POS_Y = WND_H-(PLAYER_IMAGE_SIZE*4);		// プレイヤー初期配置 y座標.

	enum class enState
	{
		None	= 1 << 0,	// 何もしてない状態.
		Jump	= 1 << 1,	// ジャンプ.
		Squat	= 1 << 2,	// しゃがみ.
		Dead	= 1 << 3,	// 死亡.
	};
public:
	CPlayer();
	~CPlayer();

	void Update() override;
	void Draw( HDC hScreenDC, HDC hMemDC ) override;

private:
	void Control();
	void JumpState();
	void SquatState();

private:
	char m_NowState;

	int m_iGravity;
};

#endif	// #ifndef PLAYER_H.