// AsoRockman
// 
// player.h
//
// 2019.11.05
//
// 1916009_Kato Toshiki


//#pragma once


// �萔
//------------------------------------------------------------------
#define NORMAL_INDEX	0
#define SHOT_INDEX		1
#define INIT_VELOCITY	50.0f	// �����x

#define ACC_RUN				0.5	//��������x
#define ACC_STOP			0.1	//��~�����x
#define VELOCITY_X_MAX		5		//X�����̑��xMAX

#define SHOT_POS 33				// �e�̔��ˈʒu�p

#define SHOT_IMGLOOK 50			// �e�̔��ˊԊu

extern CHARACTER player1;

// �������ߐ錾
//------------------------------------------------------------------
void PlayerSystemInit(void);						// ��ڲ԰1���̏�����
void PlayerGameInit(void);							// ��ڲ԰1���̹ްя�����
void PlayerControl(void);							// ��ڲ԰1�̑���
void PlayerGameDraw(void);							// ��ڲ԰1�̕`��

bool Player1HitCheck(XY sPos, XY sSize);			// player1��player2�Ƃ̓����蔻�� (true:���@������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫

bool Player1Dawn(void);								// ��ڲ԰1��ײ̂�0�̎��p