#ifndef PLAYER_H
#define PLAYER_H

#include "..\CharacterBase\CharacterBase.h"

class CPlayer : public CCharacterBase
{
	const int PLAYER_IMAGE_SIZE = 48;	// �v���C���[�摜�T�C�Y.
public:
	CPlayer();
	~CPlayer();

	void Update() override;
	void Draw( HDC hScreenDC, HDC hMemDC ) override;

private:

};

#endif	// #ifndef PLAYER_H.