// AsoRockman
// 
// player.cpp
//
// 2019.11.05
//
// 1916009_Kato Toshiki


#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "player2.h"
#include "keycheck.h"
#include "stage.h"
#include "shot2.h"
#include "effect.h"



// �ϐ�
//--------------------------------------------------------------------------------------------


CHARACTER player2;
int p2StopImage[2];			// ��~��Ԃ̉摜
int p2RunImage[2][4];		// �����Ԃ̉摜
int p2JumpImage[2];			// �ެ��ߒ��̉摜
int p2DamageImage;			// ��Ұ�މ摜
int p2TobichiriImage[6];

XY_F player2PosHit;

int lifeCnt2;

// ��ڲ԰2���̏�����
void Player2SystemInit(void)
{

	// �ϐ��̏�����
	// ��ڲ԰2
	player2.hitPosS = { 16,16 };											// ��׸��̓�����㔻��p
	player2.hitPosE = { 16,32 };											// ��׸��̓����艺����p
	player2.moveDir = DIR_RIGHT;											// ��׸��̌���
	player2.pos = { 100, SCREEN_SIZE_Y - 64 };								// ��׸��̒n�}���XY���W
	player2.size = { 96, 64 };												// ��׸��̉摜��XY����
	player2.sizeOffset = { player2.size.x / 2 ,player2.size.y / 2 };		// ��׸���OffSetXY����
	player2.moveSpeed = 5;													// ��׸��̈ړ���߰��
	player2.lifeMax = 5;													// ��׸��̗͍̑ő�l
	player2.life = player2.lifeMax;											// ��׸��̗̑�
	player2.animCnt = 0;													// ��׸��̱�Ұ���
	player2.imgLockCnt = SHOT_IMGLOOK;										// ��׸��̲Ұ�ތŒ�p����
	player2.velocity.x = 0;
	player2.velocity.y = 0;
	player2.runFlag = false;
	player2.jumpFlag = false;
	player2.shotFlag = false;
	player2.damageFlag = false;

	lifeCnt2 = 0;

	// ��~���
	p2StopImage[NORMAL_INDEX] = LoadGraph("image/stop2.png");
	p2StopImage[SHOT_INDEX] = LoadGraph("image/stop_shot2.png");
	// �ެ��ߏ��
	p2JumpImage[NORMAL_INDEX] = LoadGraph("image/jump2.png");
	p2JumpImage[SHOT_INDEX] = LoadGraph("image/jump_shot2.png");
	// �����Ă���
	LoadDivGraph("image/run2.png", 4, 4, 1, 96, 64, p2RunImage[NORMAL_INDEX]);
	LoadDivGraph("image/run_shot2.png", 4, 4, 1, 96, 64, p2RunImage[SHOT_INDEX]);
	// ��Ұ�ނ��󂯂����
	p2DamageImage = LoadGraph("image/damage2.png");


}

// ��ڲ԰2���̹ްя�����
void Player2GameInit(void)
{


	// �ϐ��̏�����
	

	// ��ڲ԰2
	player2.hitPosS = { 16,16 };											// ��׸��̓�����㔻��p
	player2.hitPosE = { 16,32 };											// ��׸��̓����艺����p
	player2.moveDir = DIR_LEFT;											// ��׸��̌���
	player2.pos = { 668, SCREEN_SIZE_Y - 64 };								// ��׸��̒n�}���XY���W
	player2.size = { 96, 64 };												// ��׸��̉摜��XY����
	player2.sizeOffset = { player2.size.x / 2 ,player2.size.y / 2 };		// ��׸���OffSetXY����
	player2.moveSpeed = 5;													// ��׸��̈ړ���߰��
	player2.lifeMax = 5;													// ��׸��̗͍̑ő�l
	player2.life = player2.lifeMax;											// ��׸��̗̑�
	player2.animCnt = 0;													// ��׸��̱�Ұ���
	player2.imgLockCnt = SHOT_IMGLOOK;										// ��׸��̲Ұ�ތŒ�p����
	player2.velocity.x = 0;
	player2.velocity.y = 0;
	player2.runFlag = false;
	player2.jumpFlag = false;
	player2.shotFlag = false;
	player2.damageFlag = false;

	lifeCnt2 = 0;
}

// ��ڲ԰2�̑���
void Player2Control(void)
{

	bool moveFlag2 = false;
	player2.runFlag = false;
	player2.shotFlag = false;
	player2.jumpFlag = true;
	player2.damageFlag = false;

	XY player2PosBK = player2.pos;
	XY player2PosHit = player2PosBK;
	XY player2PosHitUp = player2.pos;
	XY player2PosHitDown = player2.pos;
	XY player2PosHitRight = player2.pos;
	XY player2PosHitLeft = player2.pos;
	XY indexPos2;
	XY blockPos2;

	

	// �E�ړ�
	if (keyNew[KEY_ID_P2RIGHT])
	{
		moveFlag2 = true;
		player2.moveDir = DIR_RIGHT;
		player2.runFlag = true;
	}

	// ���ړ�
	if (keyNew[KEY_ID_P2LEFT])
	{
		moveFlag2 = true;
		player2.moveDir = DIR_LEFT;
		player2.runFlag = true;

	}




	// �ެ���
	if (keyNew[KEY_ID_P2UP])
	{
		if (player2.velocity.y == 0)
		{
			player2.velocity.y = INIT_VELOCITY;
		}

		player2.jumpFlag = true;
	}

	// �ެ��ߒ��̎�(Y���W�̏���)
	if (player2.jumpFlag)
	{

		// ���������^��
		//player1.pos.x += player1.velocity.x * FRAME_TIME;

		// ���x�̌v�Z							
		player2.velocity.y -= ACC_G * FRAME_TIME;

		// �����̌v�Z
		player2PosBK.y -= player2.velocity.y * FRAME_TIME;
		// player1.pos.y -= player1.velocity.y * FRAME_TIME;

		// �������ۯ�������̂���������
		// �@����̌v�Z
		player2PosHit.y = player2PosBK.y - player2.hitPosS.y;
		player2PosHitRight = player2PosHit;
		player2PosHitRight.x += player2.hitPosE.x;
		player2PosHitLeft = player2PosHit;
		player2PosHitLeft.x -= player2.hitPosS.x;
		// �A�������ۯ�����
		if (!IsPass(player2PosHit) || !IsPass(player2PosHitLeft) || !IsPass(player2PosHitRight))
		{
			// �B�������ۯ����������ꍇ�̑Ώ�
			XY blockIndex = Pos2Index(player2PosHit);
			blockIndex.y = blockIndex.y + 1;
			blockPos2 = Index2Pos(blockIndex);
			player2PosBK.y = blockPos2.y + player2.hitPosS.y;
			player2.velocity.y = -1 * player2.velocity.y;


		}

		// ��������ۯ�������̂���������
		// �@�����̌v�Z
		player2PosHit.y = player2PosBK.y + player2.hitPosE.y;
		player2PosHitRight = player2PosHit;
		player2PosHitRight.x += player2.hitPosE.x;
		player2PosHitLeft = player2PosHit;
		player2PosHitLeft.x -= player2.hitPosS.x;

		// �ެ��߂̒��n����
		// �A��������ۯ�����
		if (IsPass(player2PosHit) && IsPass(player2PosHitLeft) && IsPass(player2PosHitRight))
		{
			// �B��ۯ����Ȃ����͂��̂܂܈ړ�����
			player2.pos.y = player2PosBK.y;

		}
		else
		{
			// �B��������ۯ����������ꍇ�̑Ώ�
			// �ެ��߂̏I���͑����̍��W����ʒu������o���B
			// �����̍��W�́HplayerPosHit
			// Pos2Index(playerPosHit)������Ǝ����������ۯ���������
			// ������ۯ��̏�̖ʂ�Y���W����ڲ԰�̑������W
			// �������W������ڲ԰�̍��W���v�Z����B
			XY blockIndex = Pos2Index(player2PosHit);
			blockPos2 = Index2Pos(blockIndex);
			player2.pos.y = blockPos2.y - player2.hitPosE.y;
			player2.velocity.y = 0;
			player2.jumpFlag = false;


		}
	}

	// �ǂ̔�����������p
	player2PosBK = player2.pos;
	player2PosHit = player2PosBK;


	// �ړ����������Ă��鎞
	if (moveFlag2)
	{
		switch (player2.moveDir)
		{
		case DIR_RIGHT:
			

			player2.velocity.x += ACC_RUN;
			if (player2.velocity.x > VELOCITY_X_MAX) player2.velocity.x = VELOCITY_X_MAX;
			
			// if (Kyori(player2.pos, player2.velocity) == false) player2.velocity.x = 0;
			

			break;

		case DIR_LEFT:

			if (player2.pos.x - player1.hitPosS.x - mapPos.x > 0
				|| player1.pos.x - player2.pos.x < 500)
			{
				player2.velocity.x -= ACC_RUN;
				if (player2.velocity.x < -VELOCITY_X_MAX) player2.velocity.x = -VELOCITY_X_MAX;
			}
			
			
			// if (Kyori(player2.pos, player2.velocity) == true)player2.velocity.x = 0;

			break;

		default:
			break;
		}

	}
	// ���������Ă��Ȃ���
	else
	{
		// �����x�ɂ�錸������
		if (player2.velocity.x < 0)
		{
			// ���x�̌v�Z
			player2.velocity.x += ACC_STOP;
		}
		else if (player2.velocity.x > 0)
		{
			// ���x�̌v�Z
			player2.velocity.x -= ACC_STOP;
		}
		// ���x���قƂ�ǂȂ��ꍇ�͎~�߂��Ⴄ
		if (player2.velocity.x > -ACC_STOP && player2.velocity.x < ACC_STOP)
		{
			player2.velocity.x = 0;
		}
	}

	// ���E�̈ړ�����
	if (player2.velocity.x > 0)
	{

		player2PosBK.x += player2.velocity.x;

		player2PosHit.x = player2PosBK.x + player2.hitPosE.x;
		player2PosHitDown = player2PosHit;
		player2PosHitDown.y -= player2.hitPosS.y;
		player2PosHitUp = player2PosHit;
		player2PosHitUp.y += player2.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

		// �͈ͽ�۰�
		if (player2.pos.x - player1.pos.x < 500)
		{
			if ((player2.pos.x - mapPos.x) >= SCROLL_X_MAX)
			{
				mapPos.x += player2.velocity.x;
			}
		}
		else if (player2.pos.x + player2.hitPosS.x - mapPos.x > SCREEN_SIZE_X)
		{
			player2.velocity.x = 0;
		}

		
		
		 
	

	}
	else if (player2.velocity.x < 0)
	{

		player2PosBK.x += player2.velocity.x;

		player2PosHit.x = player2PosBK.x - player2.hitPosS.x;
		player2PosHitDown = player2PosHit;
		player2PosHitDown.y -= player2.hitPosS.y;
		player2PosHitUp = player2PosHit;
		player2PosHitUp.y += player2.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

												   // �͈ͽ�۰�
		if (player1.pos.x - player2.pos.x < 500)
		{
			if ((player2.pos.x - mapPos.x) <= SCROLL_X_MIN)
			{
				mapPos.x += player2.velocity.x;
			}
		}
		else if (player2.pos.x - player2.hitPosE.x - mapPos.x < 0)
		{
			player2.velocity.x = 0;
		}


		


	}

	if (IsPass(player2PosHit)
		&& IsPass(player2PosHitDown)
		&& IsPass(player2PosHitUp))
	{
		player2.pos.x = player2PosBK.x;
	}
	else
	{
		player2.velocity.x = 0;
	}


	// �e������
	if (keyNew[KEY_ID_P2SHOT])
	{
		XY shot2Pos = player2.pos;


		// ��ڲ԰�̌����ɍ��킹�Ēe�̔��ˈʒu�����炷
		if (player2.moveDir == DIR_RIGHT)
		{
			shot2Pos.x = player2.pos.x + SHOT_POS;
		}
		else if (player2.moveDir == DIR_LEFT)
		{
			shot2Pos.x = player2.pos.x - SHOT_POS;
		}
		// �ެ��ߒ�
		if (player2.jumpFlag == true)
		{
			shot2Pos.y = player2.pos.y - 6;
		}
		else if (player2.jumpFlag == false)
		{
			shot2Pos.y = player2.pos.y;
		}

		if (player2.imgLockCnt > SHOT_IMGLOOK)
		{
			// �e�̔��˂��˗�����
			player2.shotFlag = true;
			player2.imgLockCnt = 0;
			CreateShot2(shot2Pos, player2.moveDir);
		}



	}
	else
	{
		player2.shotFlag = false;
	}


	//----- �ړ�����
	// ϯ��
	if (mapPos.x > MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X) mapPos.x = MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X;
	if (mapPos.x < 0)mapPos.x = 0;

	// �ްђ��̶���
	if (lifeCnt2 > 0)
	{
		player2.damageFlag = true;
		lifeCnt2--;
		if (lifeCnt2 < 0)
		{
			player2.damageFlag = false;
		}
	}

	player2.animCnt++;
	player2.imgLockCnt++;
	
}

// ��ڲ԰2�̕`��
void Player2GameDraw(void)
{

	
	int playerImage2;
	int playerShotStatus2;

	playerShotStatus2 = (player2.imgLockCnt < SHOT_IMGLOOK) ? SHOT_INDEX : NORMAL_INDEX;

	playerImage2 = p2StopImage[playerShotStatus2];

	
	if (player2.runFlag) playerImage2 = p2RunImage[0][(player2.animCnt / 10 % 4)];

	if (player2.jumpFlag) playerImage2 = p2JumpImage[playerShotStatus2];

	if (player2.damageFlag) playerImage2 = p2DamageImage;



	if (player2.moveDir == DIR_LEFT)
	{
		DrawTurnGraph(player2.pos.x - player2.sizeOffset.x + -mapPos.x
			, player2.pos.y - player2.sizeOffset.y + -mapPos.y
			, playerImage2
			, true);
	}
	else if (player2.moveDir == DIR_RIGHT)
	{
		DrawGraph(player2.pos.x - player2.sizeOffset.x + -mapPos.x
			, player2.pos.y - player2.sizeOffset.y + -mapPos.y
			, playerImage2
			, true);
	}
	
	//// player�̉摜��\��
	//

	//DrawBox(player2.pos.x - player2.sizeOffset.x + -mapPos.x
	//	, player2.pos.y - player2.sizeOffset.y + -mapPos.y
	//	, player2.pos.x + player2.sizeOffset.x + -mapPos.x
	//	, player2.pos.y + player2.sizeOffset.y + -mapPos.y
	//	, GetColor(0, 0, 0)
	//	, false);

	//// player�̓����蔻��g��\��

	//DrawBox(player2.pos.x - player2.hitPosS.x + -mapPos.x
	//	, player2.pos.y - player2.hitPosS.y + -mapPos.y
	//	, player2.pos.x + player2.hitPosE.x + -mapPos.x
	//	, player2.pos.y + player2.hitPosE.y + -mapPos.y
	//	, GetColor(255, 0, 255)
	//	, false);


	XY indexPos2;

	
	indexPos2 = Pos2Index(player2.pos);

	
	//DrawFormatString(32, 48, GetColor(0, 0, 0), "player1 = ( %d : %d ) ", player2.pos.y, player2.pos.x, true);

	//DrawFormatString(32, 80, GetColor(0, 0, 0), "HitX = %d", player2PosHit, true);

	//DrawFormatString(32, 112, GetColor(0, 0, 0), "player2life = %d", player2.life, true);

	// ��ڲ԰2��HP
	SetFontSize(40);
	DrawString(675, 0, "2P", GetColor(255, 100, 0), true);

	DrawBox(418
		, 5
		, 418 + player2.lifeMax * 50
		, 32
		, GetColor(255, 0, 0), true);

	DrawBox(418
		, 5
		, 418 + player2.life * 50
		, 32
		, GetColor(0, 255, 0), true);

	DrawBox(418
		, 5
		, 418 + player2.lifeMax * 50
		, 32
		, GetColor(255, 255, 0), false);

}


// player2��player1�Ƃ̓����蔻�� (true:���@������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��
bool Player2HitCheck(XY sPos, XY sSize)
{
	// �S�Ă̓G�ɓ����蔻������{����
	if (player2.life > 0)
	{
		// ������͔�����@�͎��R (��`�ł��ǂ����A�_�Ƃ̋����ł��悢�B)
		if (((player2.pos.x - player2.hitPosS.x / 2) < (sPos.x + sSize.x / 2))
			&& ((player2.pos.x + player2.hitPosE.x / 2) > (sPos.x - sSize.x / 2))
			&& ((player2.pos.y - player2.hitPosS.y / 2) < (sPos.y + sSize.y / 2))
			&& ((player2.pos.y + player2.hitPosE.y / 2) > (sPos.y - sSize.y / 2)))
		{
			// ����������
			SetTobichiriEffect(player2.pos, EFFECT_C_RED);
			
			if (lifeCnt2 == 0) lifeCnt2 = 40;

			player2.life -= 1;

			return true;
		}

	}

	return false;
}


// ��ڲ԰2��ײ̂�0�̎��p
bool Player2Dawn(void)
{
	if (player2.life <= 0)
	{
		player2.damageFlag = true;
		return true;
	}
	else
	{
		return false;
	}
}