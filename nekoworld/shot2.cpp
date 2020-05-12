// AsoRockman
// 
// shot2.cpp
//
// 2019.12.13
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot2.h"
#include "shot.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// �ϐ�
//-------------------------------------------------------------------


CHARACTER shot2[SHOT_MAX];
int shot2Image;
XY Shot2PosHit[SHOT_MAX];



// ���ď��̏�����
void Shot2SystemInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ��׸��̎��
		shot2[sh].moveDir = DIR_DOWN;					// ��׸��̌���
		shot2[sh].pos.x = 100;								// ��׸��̒n�}���X���W
		shot2[sh].pos.y = 100;								// ��׸��̒n�}���Y���W
		shot2[sh].size.x = 16;							// ��׸����摜�̻���
		shot2[sh].size.y = 16;							// ��׸����摜�̻���
		shot2[sh].sizeOffset.x = shot2[sh].size.x / 2;	// ��׸��̵̾��
		shot2[sh].sizeOffset.y = shot2[sh].size.y / 2;	// ��׸��̵̾��
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;							// ��׸��̈ړ���߰��
		shot2[sh].life = 0;					// ��׸��̗͍̑ő�l
		shot2[sh].lifeMax = SHOT2_LIFE_MAX;
		shot2[sh].animCnt = 0;							// ��׸��̱�Ұ���
		Shot2PosHit[sh] = shot2[sh].sizeOffset;
		shot2[sh].imgLockCnt = 0;


	}

	shot2Image = LoadGraph("image/shot2.png");


}



// �e�𐶐�����
void CreateShot2(XY pPos, DIR pDir)
{
	// �e�̐��������Ă��Ȃ��e���Ȃ�����������
	// �����Ă��Ȃ��e������Έꔭ�e�𔭎˂���B

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].imgLockCnt++;

		// �����Ă��Ȃ��e��T���B
		if (shot2[sh].life <= 0)
		{
			// �����Ă��Ȃ��e���������̂Ŕ��ˁB
			// �e�̏ꏊ
			shot2[sh].pos.x = pPos.x;
			shot2[sh].pos.y = pPos.y + 6;
			// �e�̐i�ނׂ�����
			shot2[sh].moveDir = pDir;
			// �e�����������Ƃɂ���

			shot2[sh].life = shot2[sh].lifeMax;

			break;
		}


	}
}

// ���ď��̹ްя�����
void Shot2GameInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].visible = false;
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;						// ��׸��̈ړ���߰��
		shot2[sh].life = 0;								// ��׸��̗͍̑ő�l
		shot2[sh].animCnt = 0;							// ��׸��̱�Ұ���
	}
}

// ���Ă̑���
void Shot2Control(void)
{

	// �e�𓮂�������
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{

		shot2[sh].animCnt++;
		// �����Ă���e��T��
		if (shot2[sh].life > 0)
		{
			switch (shot2[sh].moveDir)
			{
			case DIR_RIGHT:
				// �e���ړ�������B
				shot2[sh].pos.x += shot2[sh].moveSpeed;
				break;

			case DIR_LEFT:
				// �e���ړ�������B
				shot2[sh].pos.x -= shot2[sh].moveSpeed;
				break;
			}

			// ���������炷

			shot2[sh].life--;


			if (!IsPass(shot2[sh].pos))
			{
				shot2[sh].life = 0;
				SetBlockEffect(shot2[sh].pos, EFFECT_C_MAGENTA);
			}
		}

	}


}

// ���Ă̕`��
void Shot2GameDraw(void)
{


	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{
			DrawGraph(shot2[sh].pos.x - shot2[sh].sizeOffset.x + -mapPos.x
				, shot2[sh].pos.y - shot2[sh].sizeOffset.y + -mapPos.y
				, shot2Image
				, true);
		}
	}



}



// �e�����ł�����
void DeleteShot2(void)
{
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{


			if (Player1HitCheck(shot2[sh].pos, shot2[sh].size)) shot2[sh].life = 0;

			if (Player1ShotHitCheck(shot2[sh].pos, shot2[sh].size))
			{
				SetTobichiriEffect(shot2[sh].pos, EFFECT_C_CYAN);

				shot2[sh].life = 0;
			}



		}
	}



}


