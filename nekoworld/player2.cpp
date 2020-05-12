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



// 変数
//--------------------------------------------------------------------------------------------


CHARACTER player2;
int p2StopImage[2];			// 停止状態の画像
int p2RunImage[2][4];		// 走り状態の画像
int p2JumpImage[2];			// ｼﾞｬﾝﾌﾟ中の画像
int p2DamageImage;			// ﾀﾞﾒｰｼﾞ画像
int p2TobichiriImage[6];

XY_F player2PosHit;

int lifeCnt2;

// ﾌﾟﾚｲﾔｰ2情報の初期化
void Player2SystemInit(void)
{

	// 変数の初期化
	// ﾌﾟﾚｲﾔｰ2
	player2.hitPosS = { 16,16 };											// ｷｬﾗｸﾀの当たり上判定用
	player2.hitPosE = { 16,32 };											// ｷｬﾗｸﾀの当たり下判定用
	player2.moveDir = DIR_RIGHT;											// ｷｬﾗｸﾀの向き
	player2.pos = { 100, SCREEN_SIZE_Y - 64 };								// ｷｬﾗｸﾀの地図上のXY座標
	player2.size = { 96, 64 };												// ｷｬﾗｸﾀの画像のXYｻｲｽﾞ
	player2.sizeOffset = { player2.size.x / 2 ,player2.size.y / 2 };		// ｷｬﾗｸﾀのOffSetXYｻｲｽﾞ
	player2.moveSpeed = 5;													// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player2.lifeMax = 5;													// ｷｬﾗｸﾀの体力最大値
	player2.life = player2.lifeMax;											// ｷｬﾗｸﾀの体力
	player2.animCnt = 0;													// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	player2.imgLockCnt = SHOT_IMGLOOK;										// ｷｬﾗｸﾀのｲﾒｰｼﾞ固定用ｶｳﾝﾀ
	player2.velocity.x = 0;
	player2.velocity.y = 0;
	player2.runFlag = false;
	player2.jumpFlag = false;
	player2.shotFlag = false;
	player2.damageFlag = false;

	lifeCnt2 = 0;

	// 停止状態
	p2StopImage[NORMAL_INDEX] = LoadGraph("image/stop2.png");
	p2StopImage[SHOT_INDEX] = LoadGraph("image/stop_shot2.png");
	// ｼﾞｬﾝﾌﾟ状態
	p2JumpImage[NORMAL_INDEX] = LoadGraph("image/jump2.png");
	p2JumpImage[SHOT_INDEX] = LoadGraph("image/jump_shot2.png");
	// 走ってる状態
	LoadDivGraph("image/run2.png", 4, 4, 1, 96, 64, p2RunImage[NORMAL_INDEX]);
	LoadDivGraph("image/run_shot2.png", 4, 4, 1, 96, 64, p2RunImage[SHOT_INDEX]);
	// ﾀﾞﾒｰｼﾞを受けた状態
	p2DamageImage = LoadGraph("image/damage2.png");


}

// ﾌﾟﾚｲﾔｰ2情報のｹﾞｰﾑ初期化
void Player2GameInit(void)
{


	// 変数の初期化
	

	// ﾌﾟﾚｲﾔｰ2
	player2.hitPosS = { 16,16 };											// ｷｬﾗｸﾀの当たり上判定用
	player2.hitPosE = { 16,32 };											// ｷｬﾗｸﾀの当たり下判定用
	player2.moveDir = DIR_LEFT;											// ｷｬﾗｸﾀの向き
	player2.pos = { 668, SCREEN_SIZE_Y - 64 };								// ｷｬﾗｸﾀの地図上のXY座標
	player2.size = { 96, 64 };												// ｷｬﾗｸﾀの画像のXYｻｲｽﾞ
	player2.sizeOffset = { player2.size.x / 2 ,player2.size.y / 2 };		// ｷｬﾗｸﾀのOffSetXYｻｲｽﾞ
	player2.moveSpeed = 5;													// ｷｬﾗｸﾀの移動ｽﾋﾟｰﾄﾞ
	player2.lifeMax = 5;													// ｷｬﾗｸﾀの体力最大値
	player2.life = player2.lifeMax;											// ｷｬﾗｸﾀの体力
	player2.animCnt = 0;													// ｷｬﾗｸﾀのｱﾆﾒｰｼｮﾝ
	player2.imgLockCnt = SHOT_IMGLOOK;										// ｷｬﾗｸﾀのｲﾒｰｼﾞ固定用ｶｳﾝﾀ
	player2.velocity.x = 0;
	player2.velocity.y = 0;
	player2.runFlag = false;
	player2.jumpFlag = false;
	player2.shotFlag = false;
	player2.damageFlag = false;

	lifeCnt2 = 0;
}

// ﾌﾟﾚｲﾔｰ2の操作
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

	

	// 右移動
	if (keyNew[KEY_ID_P2RIGHT])
	{
		moveFlag2 = true;
		player2.moveDir = DIR_RIGHT;
		player2.runFlag = true;
	}

	// 左移動
	if (keyNew[KEY_ID_P2LEFT])
	{
		moveFlag2 = true;
		player2.moveDir = DIR_LEFT;
		player2.runFlag = true;

	}




	// ｼﾞｬﾝﾌﾟ
	if (keyNew[KEY_ID_P2UP])
	{
		if (player2.velocity.y == 0)
		{
			player2.velocity.y = INIT_VELOCITY;
		}

		player2.jumpFlag = true;
	}

	// ｼﾞｬﾝﾌﾟ中の時(Y座標の処理)
	if (player2.jumpFlag)
	{

		// 等速直線運動
		//player1.pos.x += player1.velocity.x * FRAME_TIME;

		// 速度の計算							
		player2.velocity.y -= ACC_G * FRAME_TIME;

		// 距離の計算
		player2PosBK.y -= player2.velocity.y * FRAME_TIME;
		// player1.pos.y -= player1.velocity.y * FRAME_TIME;

		// 頭上にﾌﾞﾛｯｸがあるのかﾁｪｯｸする
		// ①頭上の計算
		player2PosHit.y = player2PosBK.y - player2.hitPosS.y;
		player2PosHitRight = player2PosHit;
		player2PosHitRight.x += player2.hitPosE.x;
		player2PosHitLeft = player2PosHit;
		player2PosHitLeft.x -= player2.hitPosS.x;
		// ②頭上のﾌﾞﾛｯｸﾁｪｯｸ
		if (!IsPass(player2PosHit) || !IsPass(player2PosHitLeft) || !IsPass(player2PosHitRight))
		{
			// ③頭上にﾌﾞﾛｯｸがあった場合の対処
			XY blockIndex = Pos2Index(player2PosHit);
			blockIndex.y = blockIndex.y + 1;
			blockPos2 = Index2Pos(blockIndex);
			player2PosBK.y = blockPos2.y + player2.hitPosS.y;
			player2.velocity.y = -1 * player2.velocity.y;


		}

		// 足元にﾌﾞﾛｯｸがあるのかﾁｪｯｸする
		// ①足元の計算
		player2PosHit.y = player2PosBK.y + player2.hitPosE.y;
		player2PosHitRight = player2PosHit;
		player2PosHitRight.x += player2.hitPosE.x;
		player2PosHitLeft = player2PosHit;
		player2PosHitLeft.x -= player2.hitPosS.x;

		// ｼﾞｬﾝﾌﾟの着地検査
		// ②足元のﾌﾞﾛｯｸﾁｪｯｸ
		if (IsPass(player2PosHit) && IsPass(player2PosHitLeft) && IsPass(player2PosHitRight))
		{
			// ③ﾌﾞﾛｯｸがない時はそのまま移動許可
			player2.pos.y = player2PosBK.y;

		}
		else
		{
			// ③足元にﾌﾞﾛｯｸがあった場合の対処
			// ｼﾞｬﾝﾌﾟの終了は足元の座標から位置を割り出す。
			// 足元の座標は？playerPosHit
			// Pos2Index(playerPosHit)をすると自分が乗るﾌﾞﾛｯｸが分かる
			// そのﾌﾞﾛｯｸの上の面のY座標がﾌﾟﾚｲﾔｰの足元座標
			// 足元座標からﾌﾟﾚｲﾔｰの座標を計算する。
			XY blockIndex = Pos2Index(player2PosHit);
			blockPos2 = Index2Pos(blockIndex);
			player2.pos.y = blockPos2.y - player2.hitPosE.y;
			player2.velocity.y = 0;
			player2.jumpFlag = false;


		}
	}

	// 壁の判定を初期化用
	player2PosBK = player2.pos;
	player2PosHit = player2PosBK;


	// 移動ｷｰを押している時
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
	// ｷｰを押していない時
	else
	{
		// 加速度による減速処理
		if (player2.velocity.x < 0)
		{
			// 速度の計算
			player2.velocity.x += ACC_STOP;
		}
		else if (player2.velocity.x > 0)
		{
			// 速度の計算
			player2.velocity.x -= ACC_STOP;
		}
		// 速度がほとんどない場合は止めちゃう
		if (player2.velocity.x > -ACC_STOP && player2.velocity.x < ACC_STOP)
		{
			player2.velocity.x = 0;
		}
	}

	// 左右の移動処理
	if (player2.velocity.x > 0)
	{

		player2PosBK.x += player2.velocity.x;

		player2PosHit.x = player2PosBK.x + player2.hitPosE.x;
		player2PosHitDown = player2PosHit;
		player2PosHitDown.y -= player2.hitPosS.y;
		player2PosHitUp = player2PosHit;
		player2PosHitUp.y += player2.hitPosE.y - 1;// めり込んでいる分　-1している。

		// 範囲ｽｸﾛｰﾙ
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
		player2PosHitUp.y += player2.hitPosE.y - 1;// めり込んでいる分　-1している。

												   // 範囲ｽｸﾛｰﾙ
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


	// 弾を撃つ
	if (keyNew[KEY_ID_P2SHOT])
	{
		XY shot2Pos = player2.pos;


		// ﾌﾟﾚｲﾔｰの向きに合わせて弾の発射位置をずらす
		if (player2.moveDir == DIR_RIGHT)
		{
			shot2Pos.x = player2.pos.x + SHOT_POS;
		}
		else if (player2.moveDir == DIR_LEFT)
		{
			shot2Pos.x = player2.pos.x - SHOT_POS;
		}
		// ｼﾞｬﾝﾌﾟ中
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
			// 弾の発射を依頼する
			player2.shotFlag = true;
			player2.imgLockCnt = 0;
			CreateShot2(shot2Pos, player2.moveDir);
		}



	}
	else
	{
		player2.shotFlag = false;
	}


	//----- 移動制限
	// ﾏｯﾌﾟ
	if (mapPos.x > MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X) mapPos.x = MAP_X * CHIP_SIZE_X - SCREEN_SIZE_X;
	if (mapPos.x < 0)mapPos.x = 0;

	// ｹﾞｰﾑ中のｶｳﾝﾀ
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

// ﾌﾟﾚｲﾔｰ2の描画
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
	
	//// playerの画像を表示
	//

	//DrawBox(player2.pos.x - player2.sizeOffset.x + -mapPos.x
	//	, player2.pos.y - player2.sizeOffset.y + -mapPos.y
	//	, player2.pos.x + player2.sizeOffset.x + -mapPos.x
	//	, player2.pos.y + player2.sizeOffset.y + -mapPos.y
	//	, GetColor(0, 0, 0)
	//	, false);

	//// playerの当たり判定枠を表示

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

	// ﾌﾟﾚｲﾔｰ2のHP
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


// player2とplayer1との当たり判定 (true:自機が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大きさ
bool Player2HitCheck(XY sPos, XY sSize)
{
	// 全ての敵に当たり判定を実施する
	if (player2.life > 0)
	{
		// 当たりは判定方法は自由 (矩形でも良いし、点との距離でもよい。)
		if (((player2.pos.x - player2.hitPosS.x / 2) < (sPos.x + sSize.x / 2))
			&& ((player2.pos.x + player2.hitPosE.x / 2) > (sPos.x - sSize.x / 2))
			&& ((player2.pos.y - player2.hitPosS.y / 2) < (sPos.y + sSize.y / 2))
			&& ((player2.pos.y + player2.hitPosE.y / 2) > (sPos.y - sSize.y / 2)))
		{
			// 当たった時
			SetTobichiriEffect(player2.pos, EFFECT_C_RED);
			
			if (lifeCnt2 == 0) lifeCnt2 = 40;

			player2.life -= 1;

			return true;
		}

	}

	return false;
}


// ﾌﾟﾚｲﾔｰ2のﾗｲﾌが0の時用
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