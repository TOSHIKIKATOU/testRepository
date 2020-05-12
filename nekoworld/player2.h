// AsoRockman
// 
// player2.h
//
// 2019.12.13
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

extern CHARACTER player2;

// �������ߐ錾
//------------------------------------------------------------------
void Player2SystemInit(void);						// ��ڲ԰2���̏�����
void Player2GameInit(void);							// ��ڲ԰2���̹ްя�����
void Player2Control(void);							// ��ڲ԰2�̑���
void Player2GameDraw(void);							// ��ڲ԰2�̕`��

bool Player2HitCheck(XY sPos, XY sSize);			// player2��player1�Ƃ̓����蔻�� (true:���@������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��

bool Player2Dawn(void);								// ��ڲ԰2��ײ̂�0�̎��p
