// AsoRockman
// 
// shot2.h
//
// 2019.12.13
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

void Shot2SystemInit(void);								// ���ď��̏�����
void Shot2GameInit(void);								// ���ď��̹ްя�����
void Shot2Control(void);								// ���Ă̑���
void Shot2GameDraw(void);								// ���Ă̕`��
void CreateShot2(XY pPos, DIR pDir);					// �e�𐶐�����
void DeleteShot2(void);									// �e�����ł�����

bool Player2ShotHitCheck(XY sPos, XY sSize);			// 1P�e��2P�e�Ƃ̓����蔻�� (true:1P�e������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��