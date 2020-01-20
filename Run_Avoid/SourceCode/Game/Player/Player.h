#ifndef PLAYER_H
#define PLAYER_H

#include "..\CharacterBase\CharacterBase.h"

class CPlayer : public CCharacterBase
{
	const int PLAYER_IMAGE_SIZE = 48;	// �v���C���[�摜�T�C�Y.

	const int PLAYER_INIT_POS_X = WND_W/2 - PLAYER_IMAGE_SIZE/2;	// �v���C���[�����z�u x���W.
	const int PLAYER_INIT_POS_Y = WND_H-(PLAYER_IMAGE_SIZE*4);		// �v���C���[�����z�u y���W.

	enum class enState
	{
		None	= 1 << 0,	// �������ĂȂ����.
		Jump	= 1 << 1,	// �W�����v.
		Squat	= 1 << 2,	// ���Ⴊ��.
		Dead	= 1 << 3,	// ���S.
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