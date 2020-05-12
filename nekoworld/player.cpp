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
#include "shot.h"
#include "effect.h"



// �ϐ�
//--------------------------------------------------------------------------------------------
CHARACTER player1;
int p1StopImage[2];	// ��~��Ԃ̉摜
int p1RunImage[2][4];	// �����Ԃ̉摜
int p1JumpImage[2];	// �ެ��ߒ��̉摜
int p1DamageImage;	// ��Ұ�މ摜
int p1TobichiriImage[6];

XY_F playerPosHit;

int lifeCnt;

// ��ڲ԰1���̏�����
void PlayerSystemInit(void)
{

	// �ϐ��̏�����
	// ��ڲ԰1
	player1.hitPosS = { 16,16 };											// ��׸��̓�����㔻��p
	player1.hitPosE = { 16,32 };											// ��׸��̓����艺����p
	player1.moveDir = DIR_RIGHT;											// ��׸��̌���
	player1.pos = { 100, SCREEN_SIZE_Y - 64 };								// ��׸��̒n�}���XY���W
	player1.size = { 96, 64 };												// ��׸��̉摜��XY����
	player1.sizeOffset = { player1.size.x / 2 ,player1.size.y / 2 };		// ��׸���OffSetXY����
	player1.moveSpeed = 5;													// ��׸��̈ړ���߰��
	player1.lifeMax = 5;													// ��׸��̗͍̑ő�l
	player1.life = player1.lifeMax;											// ��׸��̗̑�
	player1.animCnt = 0;													// ��׸��̱�Ұ���
	player1.imgLockCnt = SHOT_IMGLOOK;										// ��׸��̲Ұ�ތŒ�p����
	player1.velocity.x = 0;
	player1.velocity.y = 0;
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;

	lifeCnt = 0;
	

	// ��~���
	p1StopImage[NORMAL_INDEX] = LoadGraph("image/stop.png");
	p1StopImage[SHOT_INDEX] = LoadGraph("image/stop_shot.png");
	
	// �ެ��ߏ��
	p1JumpImage[NORMAL_INDEX] = LoadGraph("image/jump.png");
	p1JumpImage[SHOT_INDEX] = LoadGraph("image/jump_shot.png");
	// �����Ă���
	LoadDivGraph("image/run.png", 4, 4, 1, 96, 64, p1RunImage[NORMAL_INDEX]);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, p1RunImage[SHOT_INDEX]);
	// ��Ұ�ނ��󂯂����
	p1DamageImage = LoadGraph("image/damage.png");


}

// ��ڲ԰1���̹ްя�����
void PlayerGameInit(void)
{
	

	// �ϐ��̏�����
	// ��ڲ԰1
	player1.hitPosS = { 16,16 };											// ��׸��̓�����㔻��p
	player1.hitPosE = { 16,32 };											// ��׸��̓����艺����p
	player1.moveDir = DIR_RIGHT;											// ��׸��̌���
	player1.pos = { 100, SCREEN_SIZE_Y - 64 };								// ��׸��̒n�}���XY���W
	player1.size = { 96, 64 };												// ��׸��̉摜��XY����
	player1.sizeOffset = { player1.size.x / 2 ,player1.size.y / 2 };		// ��׸���OffSetXY����
	player1.moveSpeed = 5;													// ��׸��̈ړ���߰��
	player1.lifeMax = 5;													// ��׸��̗͍̑ő�l
	player1.life = player1.lifeMax;											// ��׸��̗̑�
	player1.animCnt = 0;													// ��׸��̱�Ұ���
	player1.imgLockCnt = SHOT_IMGLOOK;										// ��׸��̲Ұ�ތŒ�p����
	player1.velocity.x = 0;
	player1.velocity.y = 0;
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;

	lifeCnt = 0;
}

// ��ڲ԰1�̑���
void PlayerControl(void)
{

	bool moveFlag = false;
	player1.runFlag = false;
	player1.shotFlag = false;
	player1.jumpFlag = true;
	player1.damageFlag = false;
	

	XY playerPosBK = player1.pos;
	XY playerPosHit = playerPosBK;
	XY playerPosHitUp = player1.pos;
	XY playerPosHitDown = player1.pos;
	XY playerPosHitRight = player1.pos;
	XY playerPosHitLeft = player1.pos;
	XY indexPos;
	XY blockPos;

	
	// �E�ړ�
	if (keyNew[KEY_ID_P1RIGHT])
	{
		moveFlag = true;
		player1.moveDir = DIR_RIGHT;
		player1.runFlag = true;
	}
	
	// ���ړ�
	if (keyNew[KEY_ID_P1LEFT])
	{
		moveFlag = true;
		player1.moveDir = DIR_LEFT;
		player1.runFlag = true;

	}
	

	

	// �ެ���
	if (keyNew[KEY_ID_P1UP])
	{
		if (player1.velocity.y == 0)
		{
			player1.velocity.y = INIT_VELOCITY;
		}

		player1.jumpFlag = true;
	}

	// �ެ��ߒ��̎�(Y���W�̏���)
	if (player1.jumpFlag)
	{

		// ���������^��
		//player1.pos.x += player1.velocity.x * FRAME_TIME;

		// ���x�̌v�Z							
		player1.velocity.y -= ACC_G * FRAME_TIME;

		// �����̌v�Z
		playerPosBK.y -= player1.velocity.y * FRAME_TIME;
		// player1.pos.y -= player1.velocity.y * FRAME_TIME;

		// �������ۯ�������̂���������
		// �@����̌v�Z
		playerPosHit.y = playerPosBK.y - player1.hitPosS.y;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.x += player1.hitPosE.x;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.x -= player1.hitPosS.x;
		// �A�������ۯ�����
		if (!IsPass(playerPosHit) || !IsPass(playerPosHitLeft) || !IsPass(playerPosHitRight))
		{
			// �B�������ۯ����������ꍇ�̑Ώ�
			XY blockIndex = Pos2Index(playerPosHit);
			blockIndex.y = blockIndex.y + 1;
			blockPos = Index2Pos(blockIndex);
			playerPosBK.y = blockPos.y + player1.hitPosS.y;
			player1.velocity.y = -1 * player1.velocity.y;


		}

		// ��������ۯ�������̂���������
		// �@�����̌v�Z
		playerPosHit.y = playerPosBK.y + player1.hitPosE.y;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.x += player1.hitPosE.x;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.x -= player1.hitPosS.x;

		// �ެ��߂̒��n����
		// �A��������ۯ�����
		if (IsPass(playerPosHit) && IsPass(playerPosHitLeft) && IsPass(playerPosHitRight))
		{
			// �B��ۯ����Ȃ����͂��̂܂܈ړ�����
			player1.pos.y = playerPosBK.y;

		}
		else
		{
			// �B��������ۯ����������ꍇ�̑Ώ�
			// �ެ��߂̏I���͑����̍��W����ʒu������o���B
			// �����̍��W�́HplayerPosHit
			// Pos2Index(playerPosHit)������Ǝ����������ۯ���������
			// ������ۯ��̏�̖ʂ�Y���W����ڲ԰�̑������W
			// �������W������ڲ԰�̍��W���v�Z����B
			XY blockIndex = Pos2Index(playerPosHit);
			blockPos = Index2Pos(blockIndex);
			player1.pos.y = blockPos.y - player1.hitPosE.y;
			player1.velocity.y = 0;
			player1.jumpFlag = false;


		}
	}

	// �ǂ̔�����������p
	playerPosBK = player1.pos;
	playerPosHit = playerPosBK;

	// �ړ����������Ă��鎞
	if (moveFlag)
	{
		switch (player1.moveDir)
		{
		case DIR_RIGHT:

			
			player1.velocity.x += ACC_RUN;
			if (player1.velocity.x > VELOCITY_X_MAX) player1.velocity.x = VELOCITY_X_MAX;
			
			//if (Kyori2(player1.pos) == false) player1.velocity.x = 0;
			
			break;
		case DIR_LEFT:
			if (player1.pos.x - player1.hitPosE.x - mapPos.x > 0 
				|| player2.pos.x - player1.pos.x < 500)
			{
				player1.velocity.x -= ACC_RUN;
				if (player1.velocity.x < -VELOCITY_X_MAX) player1.velocity.x = -VELOCITY_X_MAX;
			}
			//if (Kyori2(player1.pos) == true)player1.velocity.x = 0;
			break;

		default:
			break;
		}

	}
	// ���������Ă��Ȃ���
	else
	{
		// �����x�ɂ�錸������
		if (player1.velocity.x < 0)
		{
			// ���x�̌v�Z
			player1.velocity.x += ACC_STOP;
		}
		else if (player1.velocity.x > 0)
		{
			// ���x�̌v�Z
			player1.velocity.x -= ACC_STOP;
		}
		// ���x���قƂ�ǂȂ��ꍇ�͎~�߂��Ⴄ
		if (player1.velocity.x > -ACC_STOP && player1.velocity.x < ACC_STOP)
		{
			player1.velocity.x = 0;
		}
	}

	// ���E�̈ړ�����
	if (player1.velocity.x > 0)
	{

		playerPosBK.x += player1.velocity.x;

		playerPosHit.x = playerPosBK.x + player1.hitPosE.x;
		playerPosHitDown = playerPosHit;
		playerPosHitDown.y -= player1.hitPosS.y;
		playerPosHitUp = playerPosHit;
		playerPosHitUp.y += player1.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

		// �͈ͽ�۰�
		if (player1.pos.x - player2.pos.x < 500)
		{
			if ((player1.pos.x - mapPos.x) >= SCROLL_X_MAX)
			{
				mapPos.x += player1.velocity.x;
			}
		}
		else if (player1.pos.x + player1.hitPosS.x - mapPos.x > SCREEN_SIZE_X)
		{
			player1.velocity.x = 0;
		}

		



	}
	else if (player1.velocity.x < 0)
	{

		playerPosBK.x += player1.velocity.x;

		playerPosHit.x = playerPosBK.x - player1.hitPosS.x;
		playerPosHitDown = playerPosHit;
		playerPosHitDown.y -= player1.hitPosS.y;
		playerPosHitUp = playerPosHit;
		playerPosHitUp.y += player1.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

		// �͈ͽ�۰�
		if (player2.pos.x - player1.pos.x < 500)
		{
			if ((player1.pos.x - mapPos.x) <= SCROLL_X_MIN)
			{
				mapPos.x += player1.velocity.x;
			}
		}
		else if (player1.pos.x - player1.hitPosE.x - mapPos.x < 0)
		{
			player1.velocity.x = 0;
		}




		
		

	}

	if (IsPass(playerPosHit)
		&& IsPass(playerPosHitDown)
		&& IsPass(playerPosHitUp))
	{
		player1.pos.x = playerPosBK.x;
	}
	else
	{
		player1.velocity.x = 0;
	}

	// �e������
	if (keyNew[KEY_ID_P1SHOT])
	{
		XY shotPos = player1.pos;

		
		// ��ڲ԰�̌����ɍ��킹�Ēe�̔��ˈʒu�����炷
		if (player1.moveDir == DIR_RIGHT)
		{
			shotPos.x = player1.pos.x + SHOT_POS;
		}
		else if (player1.moveDir == DIR_LEFT)
		{
			shotPos.x = player1.pos.x - SHOT_POS;
		}
		// �ެ��ߒ�
		if (player1.jumpFlag == true)
		{
			shotPos.y = player1.pos.y - 6;
		}
		else if (player1.jumpFlag == false)
		{
			shotPos.y = player1.pos.y;
		}

		if (player1.imgLockCnt > SHOT_IMGLOOK)
		{
			// �e�̔��˂��˗�����
			player1.shotFlag = true;
			player1.imgLockCnt = 0;
			CreateShot(shotPos, player1.moveDir);
		}
		
	}
	else
	{
		player1.shotFlag = false;
	}

	


	//----- �ړ�����
	// ϯ��
	if (mapPos.x > MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X) mapPos.x = MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X;
	if (mapPos.x < 0)mapPos.x = 0;

	// �ްђ��̶���
	if (lifeCnt > 0)
	{
		player1.damageFlag = true;
		lifeCnt--;
		if (lifeCnt < 0)
		{
			player1.damageFlag = false;
		}
	}



	player1.animCnt++;
	player1.imgLockCnt++;

}

// ��ڲ԰1�̑���
void PlayerGameDraw(void)
{

	int playerImage;
	int playerShotStatus;

	playerShotStatus = (player1.imgLockCnt < SHOT_IMGLOOK) ? SHOT_INDEX : NORMAL_INDEX;

	playerImage = p1StopImage[playerShotStatus];

	if (player1.runFlag) playerImage = p1RunImage[0][(player1.animCnt / 10 % 4)];

	if (player1.jumpFlag) playerImage = p1JumpImage[playerShotStatus];

	if (player1.damageFlag) playerImage = p1DamageImage;

	if (player1.moveDir == DIR_LEFT)
	{
		DrawTurnGraph(player1.pos.x - player1.sizeOffset.x + -mapPos.x
			, player1.pos.y - player1.sizeOffset.y + -mapPos.y
			, playerImage
			, true);
	}
	else if (player1.moveDir == DIR_RIGHT)
	{
		DrawGraph(player1.pos.x - player1.sizeOffset.x + -mapPos.x
			, player1.pos.y - player1.sizeOffset.y + -mapPos.y
			, playerImage
			, true);
	}
	
	//// player�̉摜��\��
	//DrawBox(player1.pos.x - player1.sizeOffset.x + -mapPos.x
	//	, player1.pos.y - player1.sizeOffset.y + -mapPos.y
	//	, player1.pos.x + player1.sizeOffset.x + -mapPos.x
	//	, player1.pos.y + player1.sizeOffset.y + -mapPos.y
	//	, GetColor(0, 0, 0)
	//	, false);

	//// player�̓����蔻��g��\��
	//DrawBox(player1.pos.x - player1.hitPosS.x + -mapPos.x
	//	, player1.pos.y - player1.hitPosS.y + -mapPos.y
	//	, player1.pos.x + player1.hitPosE.x + -mapPos.x
	//	, player1.pos.y + player1.hitPosE.y + -mapPos.y
	//	, GetColor(255, 0, 255)
	//	, false);

	XY indexPos;

	indexPos = Pos2Index(player1.pos);

	//DrawFormatString(32, 32, GetColor(0, 0, 0), "player1 = ( %d : %d ) ", player1.pos.y, player1.pos.x, true);

	//DrawFormatString(32, 64, GetColor(0, 0, 0), "HitX = %d", playerPosHit, true);

	//DrawFormatString(32, 96, GetColor(0, 0, 0), "player1life = %d", player1.life, true);


	

	// ��ڲ԰1��HP
	SetFontSize(40);
	DrawString(50, 0, "1P", GetColor(0, 0, 255), true);

	DrawBox(350
		, 5
		, 350 + player1.lifeMax * -50
		, 32
		, GetColor(255, 0, 0), true);

	DrawBox(350
		, 5
		, 350 + player1.life * -50
		, 32
		, GetColor(0, 255, 0), true);

	DrawBox(350
		, 5
		, 350 + player1.lifeMax * -50
		, 32
		, GetColor(255, 255, 0), false);
}

// player1��player2�Ƃ̓����蔻�� (true:���@������������ ,false:�e���O�ꂽ��)���� : �e�̍��W , �e�̑傫��
bool Player1HitCheck(XY sPos, XY sSize)
{
	// �S�Ă̓G�ɓ����蔻������{����
	

	if (player1.life > 0)
	{
		// ������͔�����@�͎��R (��`�ł��ǂ����A�_�Ƃ̋����ł��悢�B)
		if (((player1.pos.x - player1.hitPosS.x / 2) < (sPos.x + sSize.x / 2))
			&& ((player1.pos.x + player1.hitPosE.x / 2) > (sPos.x - sSize.x / 2))
			&& ((player1.pos.y - player1.hitPosS.y / 2) < (sPos.y + sSize.y / 2))
			&& ((player1.pos.y + player1.hitPosE.y / 2) > (sPos.y - sSize.y / 2)))
		{
			// ����������
			SetTobichiriEffect(player1.pos, EFFECT_C_CYAN);
		
			if (lifeCnt == 0) lifeCnt = 40;
			
			if (player1.life > 0) player1.life -= 1;
			
			return true;
		}

	}

	
	return false;

}

// ��ڲ԰1��ײ̂�0�̎��p
bool Player1Dawn(void)
{
	if (player1.life <= 0)
	{
		player1.damageFlag = true;
		return true;
	}
	else
	{
		return false;
	}
}