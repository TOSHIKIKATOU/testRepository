// AsoRockman
// 
// shot.cpp
//
// 2019.11.21
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot.h"
#include "shot2.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// �ϐ�
//-------------------------------------------------------------------
CHARACTER shot[SHOT_MAX];
int shotImage;
XY ShotPosHit[SHOT_MAX];


// ���ď��̏�����
void ShotSystemInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ��׸��̎��
		shot[sh].moveDir = DIR_DOWN;					// ��׸��̌���
		shot[sh].pos.x = 150;								// ��׸��̒n�}���X���W
		shot[sh].pos.y = 150;								// ��׸��̒n�}���Y���W
		shot[sh].size.x = 16;							// ��׸����摜�̻���
		shot[sh].size.y = 16;							// ��׸����摜�̻���
		shot[sh].sizeOffset.x = shot[sh].size.x / 2;	// ��׸��̵̾��
		shot[sh].sizeOffset.y = shot[sh].size.y / 2;	// ��׸��̵̾��
		shot[sh].moveSpeed = SHOT_DEF_SPEED;							// ��׸��̈ړ���߰��
		shot[sh].life = 0;					// ��׸��̗͍̑ő�l
		shot[sh].lifeMax = SHOT_LIFE_MAX;
		shot[sh].animCnt = 0;							// ��׸��̱�Ұ���
		ShotPosHit[sh] = shot[sh].sizeOffset;
		shot[sh].imgLockCnt = 0;

	}

	

	shotImage = LoadGraph("image/shot1.png");


}

// �e�𐶐�����
void CreateShot(XY pPos, DIR pDir)
{
	// �e�̐��������Ă��Ȃ��e���Ȃ�����������
	// �����Ă��Ȃ��e������Έꔭ�e�𔭎˂���B
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].imgLockCnt++;

		// �����Ă��Ȃ��e��T���B
		if (shot[sh].life <= 0)
		{
			// �����Ă��Ȃ��e���������̂Ŕ��ˁB
			// �e�̏ꏊ
			shot[sh].pos.x = pPos.x;
			shot[sh].pos.y = pPos.y + 6;
			// �e�̐i�ނׂ�����
			shot[sh].moveDir = pDir;
			// �e�����������Ƃɂ���

			shot[sh].life = shot[sh].lifeMax;

			break;
		}

	}


}

// ���ď��̹ްя�����
void ShotGameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].visible = false;
		shot[sh].moveSpeed = SHOT_DEF_SPEED;						// ��׸��̈ړ���߰��
		shot[sh].life = 0;								// ��׸��̗͍̑ő�l
		shot[sh].animCnt = 0;							// ��׸��̱�Ұ���

	}


}

// ���Ă̑���
void ShotControl(void)
{
	

	// �e�𓮂�������
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		XY shotPosCopy = shot[sh].pos;
		XY shotPosOffset = shotPosCopy;

		shot[sh].animCnt++;
		// �����Ă���e��T��
		if (shot[sh].life > 0)
		{
			switch (shot[sh].moveDir)
			{
			case DIR_RIGHT:
				// �e���ړ�������B
				shotPosCopy.x += shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;

			case DIR_LEFT:
				// �e���ړ�������B
				shotPosCopy.x -= shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;
			}

			// ���������炷
			shot[sh].life--;


			if (!IsPass(shotPosOffset))
			{
				SetBlockEffect(shot[sh].pos, EFFECT_C_YELLOW);
			}
		}

	}

	


}

// ���Ă̕`��
void ShotGameDraw(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			DrawGraph(shot[sh].pos.x - shot[sh].sizeOffset.x + -mapPos.x
				, shot[sh].pos.y - shot[sh].sizeOffset.y + -mapPos.y
				, shotImage
				, true);



		}


	}
}

// �e�����ł�����
void DeleteShot(void)
{
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			if (Player2HitCheck(shot[sh].pos, shot[sh].size))shot[sh].life = 0;

			/*if (Player2ShotHitCheck(shot[sh].pos, shot[sh].size))
			{
				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				
			}*/
		}

	}



}

// 1P�e��2P�e�Ƃ̓����蔻�� (true:1P�e������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��
bool Player1ShotHitCheck(XY sPos, XY sSize)
{
	// �S�Ă̓G�ɓ����蔻������{����
	
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{

		if (shot[sh].life > 0)
		{
			// ������͔�����@�͎��R (��`�ł��ǂ����A�_�Ƃ̋����ł��悢�B)
			if (((shot[sh].pos.x - shot[sh].size.x / 2) < (sPos.x + sSize.x / 2))
				&& ((shot[sh].pos.x + shot[sh].size.x / 2) > (sPos.x - sSize.x / 2))
				&& ((shot[sh].pos.y - shot[sh].size.y / 2) < (sPos.y + sSize.y / 2))
				&& ((shot[sh].pos.y + shot[sh].size.y / 2) > (sPos.y - sSize.y / 2)))
			{
				// ����������

				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				shot[sh].life = 0;

				return true;
			}
		}
		

	}


	return false;

}
