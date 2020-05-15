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



// 変数
//--------------------------------------------------------------------------------------------
CHARACTER player1;
int p1StopImage[2];	// 停止状態の画像
int p1RunImage[2][4];	// 走り状態の画像
int p1JumpImage[2];	// ｼﾞｬﾝﾌﾟ中の画像
int p1DamageImage;	// ﾀﾞﾒｰｼﾞ画像
int p1TobichiriImage[6];

XY_F playerPosHit;

int lifeCnt;

// ﾌﾟﾚｲﾔｰ1情報の初期化
void PlayerSystemInit(void)
{

	// 変数の初期化
	// ﾌﾟﾚｲﾔｰ1
	player1.hitPosS = { 16,16 };											// ｷｬﾗｸﾀの当たり上判定用
	player1.hitPosE = { 16,32 };											// ｷｬﾗｸﾀの当たり下判定用
	player1.moveDir = DIR_RIGHT;											// ｷｬﾗｸﾀの向き
	player1.pos = { 100, SCREEN_SIZE_Y - 64 };								// ｷｬﾗｸﾀの地図上のXY座標
	player1.size = { 96, 64 };												// ｷｬﾗｸﾀの画像のXYｻｲｽﾞ
	player1.sizeOffset = { player1.size.x / 2 ,player1.size.y / 2 };		// ｷｬﾗｸﾀのOffSetXYｻｲｽﾞ
	player1.moveSpeed = 5;													// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player1.lifeMax = 5;													// ｷｬﾗｸﾀの体力最大値
	player1.life = player1.lifeMax;											// ｷｬﾗｸﾀの体力
	player1.animCnt = 0;													// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	player1.imgLockCnt = SHOT_IMGLOOK;										// ｷｬﾗｸﾀのｲﾒｰｼﾞ固定用ｶｳﾝﾀ
	player1.velocity.x = 0;
	player1.velocity.y = 0;
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;

	lifeCnt = 0;

	//SetTransColor(255, 255, 255);		// 指定した色を透過する
	

	// 停止状態
	p1StopImage[NORMAL_INDEX] = LoadGraph("image/stop.png");
	p1StopImage[SHOT_INDEX] = LoadGraph("image/stop_shot.png");
	
	// ｼﾞｬﾝﾌﾟ状態
	p1JumpImage[NORMAL_INDEX] = LoadGraph("image/jump.png");
	p1JumpImage[SHOT_INDEX] = LoadGraph("image/jump_shot.png");

	// 走ってる状態
	LoadDivGraph("image/running.png", 2, 2, 1, 80, 80, p1RunImage[NORMAL_INDEX]);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, p1RunImage[SHOT_INDEX]);
	// ﾀﾞﾒｰｼﾞを受けた状態
	p1DamageImage = LoadGraph("image/damage.png");


}

// ﾌﾟﾚｲﾔｰ1情報のｹﾞｰﾑ初期化
void PlayerGameInit(void)
{
	

	// 変数の初期化
	// ﾌﾟﾚｲﾔｰ1
	player1.hitPosS = { 16,16 };											// ｷｬﾗｸﾀの当たり上判定用
	player1.hitPosE = { 16,32 };											// ｷｬﾗｸﾀの当たり下判定用
	player1.moveDir = DIR_RIGHT;											// ｷｬﾗｸﾀの向き
	player1.pos = { 100, SCREEN_SIZE_Y - 64 };								// ｷｬﾗｸﾀの地図上のXY座標
	player1.size = { 96, 64 };												// ｷｬﾗｸﾀの画像のXYｻｲｽﾞ
	player1.sizeOffset = { player1.size.x / 2 ,player1.size.y / 2 };		// ｷｬﾗｸﾀのOffSetXYｻｲｽﾞ
	player1.moveSpeed = 5;													// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player1.lifeMax = 5;													// ｷｬﾗｸﾀの体力最大値
	player1.life = player1.lifeMax;											// ｷｬﾗｸﾀの体力
	player1.animCnt = 0;													// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	player1.imgLockCnt = SHOT_IMGLOOK;										// ｷｬﾗｸﾀのｲﾒｰｼﾞ固定用ｶｳﾝﾀ
	player1.velocity.x = 0;
	player1.velocity.y = 0;
	player1.runFlag = false;
	player1.jumpFlag = false;
	player1.shotFlag = false;
	player1.damageFlag = false;

	lifeCnt = 0;
}

// ﾌﾟﾚｲﾔｰ1の操作
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

	
	// 右移動
	if (keyNew[KEY_ID_P1RIGHT])
	{
		moveFlag = true;
		player1.moveDir = DIR_RIGHT;
		player1.runFlag = true;
	}
	
	// 左移動
	if (keyNew[KEY_ID_P1LEFT])
	{
		moveFlag = true;
		player1.moveDir = DIR_LEFT;
		player1.runFlag = true;

	}
	

	

	// ｼﾞｬﾝﾌﾟ
	if (keyNew[KEY_ID_P1UP])
	{
		if (player1.velocity.y == 0)
		{
			player1.velocity.y = INIT_VELOCITY;
		}

		player1.jumpFlag = true;
	}

	// ｼﾞｬﾝﾌﾟ中の時(Y座標の処理)
	if (player1.jumpFlag)
	{

		// 等速直線運動
		//player1.pos.x += player1.velocity.x * FRAME_TIME;

		// 速度の計算							
		player1.velocity.y -= ACC_G * FRAME_TIME;

		// 距離の計算
		playerPosBK.y -= player1.velocity.y * FRAME_TIME;
		// player1.pos.y -= player1.velocity.y * FRAME_TIME;

		// 頭上にﾌﾞﾛｯｸがあるのかﾁｪｯｸする
		// ①頭上の計算
		playerPosHit.y = playerPosBK.y - player1.hitPosS.y;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.x += player1.hitPosE.x;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.x -= player1.hitPosS.x;
		// ②頭上のﾌﾞﾛｯｸﾁｪｯｸ
		if (!IsPass(playerPosHit) || !IsPass(playerPosHitLeft) || !IsPass(playerPosHitRight))
		{
			// ③頭上にﾌﾞﾛｯｸがあった場合の対処
			XY blockIndex = Pos2Index(playerPosHit);
			blockIndex.y = blockIndex.y + 1;
			blockPos = Index2Pos(blockIndex);
			playerPosBK.y = blockPos.y + player1.hitPosS.y;
			player1.velocity.y = -1 * player1.velocity.y;


		}

		// 足元にﾌﾞﾛｯｸがあるのかﾁｪｯｸする
		// ①足元の計算
		playerPosHit.y = playerPosBK.y + player1.hitPosE.y;
		playerPosHitRight = playerPosHit;
		playerPosHitRight.x += player1.hitPosE.x;
		playerPosHitLeft = playerPosHit;
		playerPosHitLeft.x -= player1.hitPosS.x;

		// ｼﾞｬﾝﾌﾟの着地検査
		// ②足元のﾌﾞﾛｯｸﾁｪｯｸ
		if (IsPass(playerPosHit) && IsPass(playerPosHitLeft) && IsPass(playerPosHitRight))
		{
			// ③ﾌﾞﾛｯｸがない時はそのまま移動許可
			player1.pos.y = playerPosBK.y;

		}
		else
		{
			// ③足元にﾌﾞﾛｯｸがあった場合の対処
			// ｼﾞｬﾝﾌﾟの終了は足元の座標から位置を割り出す。
			// 足元の座標は？playerPosHit
			// Pos2Index(playerPosHit)をすると自分が乗るﾌﾞﾛｯｸが分かる
			// そのﾌﾞﾛｯｸの上の面のY座標がﾌﾟﾚｲﾔｰの足元座標
			// 足元座標からﾌﾟﾚｲﾔｰの座標を計算する。
			XY blockIndex = Pos2Index(playerPosHit);
			blockPos = Index2Pos(blockIndex);
			player1.pos.y = blockPos.y - player1.hitPosE.y;
			player1.velocity.y = 0;
			player1.jumpFlag = false;


		}
	}

	// 壁の判定を初期化用
	playerPosBK = player1.pos;
	playerPosHit = playerPosBK;

	// 移動ｷｰを押している時
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
	// ｷｰを押していない時
	else
	{
		// 加速度による減速処理
		if (player1.velocity.x < 0)
		{
			// 速度の計算
			player1.velocity.x += ACC_STOP;
		}
		else if (player1.velocity.x > 0)
		{
			// 速度の計算
			player1.velocity.x -= ACC_STOP;
		}
		// 速度がほとんどない場合は止めちゃう
		if (player1.velocity.x > -ACC_STOP && player1.velocity.x < ACC_STOP)
		{
			player1.velocity.x = 0;
		}
	}

	// 左右の移動処理
	if (player1.velocity.x > 0)
	{

		playerPosBK.x += player1.velocity.x;

		playerPosHit.x = playerPosBK.x + player1.hitPosE.x;
		playerPosHitDown = playerPosHit;
		playerPosHitDown.y -= player1.hitPosS.y;
		playerPosHitUp = playerPosHit;
		playerPosHitUp.y += player1.hitPosE.y - 1;// めり込んでいる分　-1している。

		// 範囲ｽｸﾛｰﾙ
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
		playerPosHitUp.y += player1.hitPosE.y - 1;// めり込んでいる分　-1している。

		// 範囲ｽｸﾛｰﾙ
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

	// 弾を撃つ
	if (keyNew[KEY_ID_P1SHOT])
	{
		XY shotPos = player1.pos;

		
		// ﾌﾟﾚｲﾔｰの向きに合わせて弾の発射位置をずらす
		if (player1.moveDir == DIR_RIGHT)
		{
			shotPos.x = player1.pos.x + SHOT_POS;
		}
		else if (player1.moveDir == DIR_LEFT)
		{
			shotPos.x = player1.pos.x - SHOT_POS;
		}
		// ｼﾞｬﾝﾌﾟ中
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
			// 弾の発射を依頼する
			player1.shotFlag = true;
			player1.imgLockCnt = 0;
			CreateShot(shotPos, player1.moveDir);
		}
		
	}
	else
	{
		player1.shotFlag = false;
	}

	


	//----- 移動制限
	// ﾏｯﾌﾟ
	if (mapPos.x > MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X) mapPos.x = MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X;
	if (mapPos.x < 0)mapPos.x = 0;

	// ｹﾞｰﾑ中のｶｳﾝﾀ
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

// ﾌﾟﾚｲﾔｰ1の操作
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
	
	//// playerの画像を表示
	//DrawBox(player1.pos.x - player1.sizeOffset.x + -mapPos.x
	//	, player1.pos.y - player1.sizeOffset.y + -mapPos.y
	//	, player1.pos.x + player1.sizeOffset.x + -mapPos.x
	//	, player1.pos.y + player1.sizeOffset.y + -mapPos.y
	//	, GetColor(0, 0, 0)
	//	, false);

	//// playerの当たり判定枠を表示
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


	

	// ﾌﾟﾚｲﾔｰ1のHP
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

// player1とplayer2との当たり判定 (true:自機が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大きさ
bool Player1HitCheck(XY sPos, XY sSize)
{
	// 全ての敵に当たり判定を実施する
	

	if (player1.life > 0)
	{
		// 当たりは判定方法は自由 (矩形でも良いし、点との距離でもよい。)
		if (((player1.pos.x - player1.hitPosS.x / 2) < (sPos.x + sSize.x / 2))
			&& ((player1.pos.x + player1.hitPosE.x / 2) > (sPos.x - sSize.x / 2))
			&& ((player1.pos.y - player1.hitPosS.y / 2) < (sPos.y + sSize.y / 2))
			&& ((player1.pos.y + player1.hitPosE.y / 2) > (sPos.y - sSize.y / 2)))
		{
			// 当たった時
			SetTobichiriEffect(player1.pos, EFFECT_C_CYAN);
		
			if (lifeCnt == 0) lifeCnt = 40;
			
			if (player1.life > 0) player1.life -= 1;
			
			return true;
		}

	}

	
	return false;

}

// ﾌﾟﾚｲﾔｰ1のﾗｲﾌが0の時用
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