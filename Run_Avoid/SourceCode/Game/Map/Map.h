#ifndef MAP_H
#define MAP_H

class CMap
{
	const int MAP_IMAGE_SIZE	= 48;	// �}�b�v�̉摜�T�C�Y.
	const int MAP_SIZE_X		= 17;	// �}�b�v�`�b�v�̃T�C�Y.
	const int MAP_SIZE_Y		= 10;	// �}�b�v�`�b�v�̃T�C�Y.
	const int GOAL_MAP_SIZE_X	= 9;	// �S�[���p�}�b�v�`�b�v�̃T�C�Y.
	const int MAP_SCROLL_SPD	= 4;	// �}�b�v�X�N���[���̑���.

	const int GOAL_DISTANCE		= 100;	// �S�[���܂ł̋���.

	const char* MAP_DATA_PATH		= "Data\\MAP\\mapchipdata.txt";
	const char* GOAL_MAP_DATE_PATH	= "Data\\MAP\\mapchipgoaldata.txt";
public:
	CMap();
	~CMap();

	// �X�V�֐�.
	void Update();
	// �`��֐�.
	void Draw( HDC hScreenDC, HDC hMemDC );

private:
	// �}�b�v�X�N���[���֐�.
	void Scroll();
	// �}�b�v�t�X�N���[��.
	void BackScroll();
	// �S�[���}�b�v�X�N���[���֐�.
	void GoalScroll();
	// �}�b�v�̓ǂݍ���.
	void MapLoad();	
	// �S�[���}�b�v�̓ǂݍ���.
	void GoalMalLoad();

private:
	HBITMAP	m_hMapBmp;		// �}�b�v�摜.
	int**	m_iMapChip;		// �}�b�v���.
	int**	m_iGoalMapChip;	// �S�[���}�b�v���.

	int*	m_iBufferMap;	// �X�N���[���p

	int		m_iScrollPosX;	// �X�N���[�����W.
	int		m_RunDistance;	// �����Ă��鋗��.
	int		m_iGoalCount;	// �S�[���J�E���g.

};

#endif	// #ifndef MAP_H.