// AsoRockman
// 
// shot.h
//
// 2019.11.21
//
// 1916009_Kato Toshiki

//#pragma once

// �萔
//------------------------------------------------------------------
#define SHOT_MAX 50
#define SHOT_DEF_SPEED  12
#define SHOT_LIFE_MAX 40

#define SHOT2_MAX 50
#define SHOT2_DEF_SPEED  12
#define SHOT2_LIFE_MAX 40

// extern�錾
//-------------------------------------------------------------------
// extern CHARACTER shot[SHOT_MAX];

// �������ߐ錾
//---------------------------------------------------------------------

void ShotSystemInit(void);								// ���ď��̏�����
void ShotGameInit(void);								// ���ď��̹ްя�����
void ShotControl(void);									// ���Ă̑���
void ShotGameDraw(void);								// ���Ă̕`��
void CreateShot(XY pPos, DIR pDir);						// �e�𐶐�����
void DeleteShot(void);									// �e�����ł�����

bool Player1ShotHitCheck(XY sPos, XY sSize);			// 1P�e��2P�e�Ƃ̓����蔻�� (true:1P�e������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��