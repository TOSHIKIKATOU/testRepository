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
#include "keycheck.h"
#include "stage.h"
#include "shot.h"



#define NORMAL_INDEX	0
#define SHOT_INDEX		1
#define INIT_VELOCITY	50.0f	// �����x

#define ACC_RUN				0.5	//��������x
#define ACC_STOP			0.1	//��~�����x
#define VELOCITY_X_MAX		7		//X�����̑��xMAX


// �ϐ�
//--------------------------------------------------------------------------------------------
CHARACTER player1;
int p1StopImage[2];	// ��~��Ԃ̉摜
int p1RunImage[2][4];	// �����Ԃ̉摜
int p1JumpImage[2];	// �ެ��ߒ��̉摜

int p1DamageImage;	// ��Ұ�މ摜
int p1TobichiriImage[6];

XY_F playerPosHit;

void PlayerSystemInit(void)
{

	// �\���̂̏�����
	// player1.chartype;								// ��׸��̎��
	player1.hitPosS = { 16,16 };
	player1.hitPosE = { 16,32 };
	player1.moveDir = DIR_RIGHT;						// ��׸��̌���
	 player1.pos = { 100, SCREEN_SIZE_Y - 64 };
	//player1.pos.x = 100;							// ��׸��̒n�}���X���W
	//player1.pos.y = 385;							// ��׸��̒n�}���Y���W	
	player1.size = { 96, 64 };
	// player1.size.x = 96;							// ��׸����摜�̻���
	// player1.size.y = 64;							// ��׸����摜�̻���
	player1.sizeOffset = { player1.size.x / 2 ,player1.size.y / 2 };
	player1.moveSpeed = 5;							// ��׸��̈ړ���߰��
	player1.lifeMax = 5;							// ��׸��̗͍̑ő�l
	player1.life = player1.lifeMax;					// ��׸��̗̑�
	player1.animCnt = 0;							// ��׸��̱�Ұ���
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;

	// ���������^��
	//velocity0.x = 0.0f;	// [m/s]
	player1.velocity.x = 0;
	//velocity0.y = 80.0f;	// [m/s]
	player1.velocity.y = 0;

	// ��~���
	p1StopImage[NORMAL_INDEX] = LoadGraph("image/stop.png");
	p1StopImage[SHOT_INDEX] = LoadGraph("image/stop_shot.png");
	// �ެ��ߏ��
	p1JumpImage[NORMAL_INDEX] = LoadGraph("image/jump.png");
	p1JumpImage[SHOT_INDEX] = LoadGraph("image/jump_shot.png");
	// �����Ă���
	LoadDivGraph("image/run.png", 4, 4, 1, 96, 64, p1RunImage[NORMAL_INDEX]);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, p1RunImage[SHOT_INDEX]);
	// 
	p1DamageImage = LoadGraph("image/damage.png");


}


void PlayerGameInit(void)
{

}


void PlayerControl(void)
{

	bool moveFlag = false;
	player1.runFlag = false;
	player1.shotFlag = false;
	player1.jumpFlag = true;
	XY playerPosBK = player1.pos;
	XY playerPosHit = playerPosBK;
	XY playerPosHitLeft = player1.pos;
	XY playerPosHitRight = player1.pos;

	XY indexPos;
	XY blockPos;
	

	if (CheckHitKey(KEY_INPUT_D))
	{
		mapPos.x++;
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		mapPos.x--;
	}

	// �E�ړ�
	if (keyNew[KEY_ID_RIGHT])
	{
		moveFlag = true;
		player1.moveDir = DIR_RIGHT;
		player1.runFlag = true;
	}
	
	// ���ړ�
	if (keyNew[KEY_ID_LEFT])
	{
		moveFlag = true;
		player1.moveDir = DIR_LEFT;
		player1.runFlag = true;

	}
	
	// �e������
	if (keyNew[KEY_ID_SHOT]) 
	{
		player1.shotFlag = true;

		// �e�̔��˂��˗�����
		CreateShot(player1.pos, player1.moveDir);
	}
	else
	{
		player1.shotFlag = false;
	}

	// �ެ���
	if (keyNew[KEY_ID_JUMP])
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
		if (!IsPass(playerPosHit) || !IsPass(playerPosHitRight) || !IsPass(playerPosHitLeft))
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
		if (IsPass(playerPosHit) && IsPass(playerPosHitRight) && IsPass(playerPosHitLeft))
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

	// ���E�̈ړ�����
	if (moveFlag)
	{
		switch (player1.moveDir)
		{
		case DIR_RIGHT:

			if (player1.velocity.x > VELOCITY_X_MAX) player1.velocity.x = VELOCITY_X_MAX;
			player1.velocity.x += ACC_RUN;
			break;

		case DIR_LEFT:

			if (player1.velocity.x < -VELOCITY_X_MAX) player1.velocity.x = -VELOCITY_X_MAX;
			player1.velocity.x -= ACC_RUN;
			break;

		default:
			break;
		}

	}
	else
	{
		if (player1.velocity.x < 0)
		{
			player1.velocity.x += ACC_STOP;
		}
		else if (player1.velocity.x > 0)
		{
			player1.velocity.x -= ACC_STOP;
		}
		// ���x���قƂ�ǂȂ��ꍇ�͎~�߂��Ⴄ
		if (player1.velocity.x > -ACC_STOP && player1.velocity.x < ACC_STOP)
		{
			player1.velocity.x = 0;
		}
	}


	if (player1.velocity.x > 0)
	{

		playerPosBK.x += player1.velocity.x;

		playerPosHit.x = playerPosBK.x + player1.hitPosE.x;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.y -= player1.hitPosS.y;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.y += player1.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

	}
	else if (player1.velocity.x < 0)
	{

		playerPosBK.x += player1.velocity.x;

		playerPosHit.x = playerPosBK.x - player1.hitPosS.x;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.y -= player1.hitPosS.y;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.y += player1.hitPosE.y - 1;// �߂荞��ł��镪�@-1���Ă���B

	}

	if (IsPass(playerPosHit)
		&& IsPass(playerPosHitRight)
		&& IsPass(playerPosHitLeft))
	{
		player1.pos.x = playerPosBK.x;
	}
	else
	{
		player1.velocity.x = 0;
	}


	player1.animCnt++;
}


void PlayerGameDraw(void)
{
	int playerImage;
	int playerShotStatus;

	playerShotStatus = (player1.shotFlag) ? SHOT_INDEX : NORMAL_INDEX;

	/*{
		playerShotStatus = SHOT_INDEX;
	}
	else
	{
		playerShotStatus = NORMAL_INDEX;
	}*/

	// playerShotStatus = (player1.shotFlag);

	playerImage = p1StopImage[playerShotStatus];
	if (player1.runFlag) playerImage = p1RunImage[0][(player1.animCnt / 10 % 4)];

	if (player1.jumpFlag) playerImage = p1JumpImage[playerShotStatus];

	/*{
		playerImage = p1RunImage[0][(player1.animCnt / 20 % 4)];
	}
	else
	{
		playerImage = p1StopImage[0];
	}*/


	// DrawGraph(100, 0, p1DamageImage, true);


	if (player1.moveDir == DIR_LEFT)
	{
		DrawTurnGraph(player1.pos.x-player1.sizeOffset.x + -mapPos.x
			, player1.pos.y- player1.sizeOffset.y + -mapPos.y
			, playerImage
			, true);
	}
	else
	{
		DrawGraph(player1.pos.x - player1.sizeOffset.x + -mapPos.x
			, player1.pos.y - player1.sizeOffset.y + -mapPos.y
			, playerImage
			, true);
	}

	// player�̉摜��\��
	DrawBox(player1.pos.x - player1.sizeOffset.x + -mapPos.x
		, player1.pos.y - player1.sizeOffset.y + -mapPos.y
		, player1.pos.x + player1.sizeOffset.x + -mapPos.x
		, player1.pos.y + player1.sizeOffset.y + -mapPos.y
		, GetColor(0, 0, 0)
		, false);

	// player�̓����蔻��g��\��
	DrawBox(player1.pos.x - player1.hitPosS.x + -mapPos.x
		, player1.pos.y - player1.hitPosS.y + -mapPos.y
		, player1.pos.x + player1.hitPosE.x + -mapPos.x
		, player1.pos.y + player1.hitPosE.y + -mapPos.y
		, GetColor(255, 0, 255)
		, false);




		
	
	XY indexPos;

	indexPos = Pos2Index(player1.pos);

	DrawFormatString(32, 32, GetColor(0, 0, 0), "player1 = ( %d : %d ) ", player1.pos.y, player1.pos.x, true);

	DrawFormatString(32, 48, GetColor(0, 0, 0), "HitX = %d", playerPosHit, true);

	// DrawFormatString(32, 64, GetColor(0, 0, 0), "velocity = ( %.5f : %.5f ) ", player1.velocity.y, player1.velocity.x, true);

	/*DrawGraph(100, 70, p1StopImage[1], true);

	DrawGraph(100, 140, p1JumpImage[0], true);

	DrawGraph(100, 210, p1JumpImage[1], true);

	DrawGraph(100, 280, p1RunImage[0][0], true);

	DrawGraph(100, 350, p1RunImage[1][0], true);*/

}



