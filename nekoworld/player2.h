// AsoRockman
// 
// player2.h
//
// 2019.12.13
//
// 1916009_Kato Toshiki


//#pragma once


// 定数
//------------------------------------------------------------------
#define NORMAL_INDEX	0
#define SHOT_INDEX		1
#define INIT_VELOCITY	50.0f	// 初速度

#define ACC_RUN				0.5	//走る加速度
#define ACC_STOP			0.1	//停止加速度
#define VELOCITY_X_MAX		5		//X方向の速度MAX

#define SHOT_POS 33				// 弾の発射位置用

#define SHOT_IMGLOOK 50			// 弾の発射間隔

extern CHARACTER player2;

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//------------------------------------------------------------------
void Player2SystemInit(void);						// ﾌﾟﾚｲﾔｰ2情報の初期化
void Player2GameInit(void);							// ﾌﾟﾚｲﾔｰ2情報のｹﾞｰﾑ初期化
void Player2Control(void);							// ﾌﾟﾚｲﾔｰ2の操作
void Player2GameDraw(void);							// ﾌﾟﾚｲﾔｰ2の描画

bool Player2HitCheck(XY sPos, XY sSize);			// player2とplayer1との当たり判定 (true:自機が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大きさ

bool Player2Dawn(void);								// ﾌﾟﾚｲﾔｰ2のﾗｲﾌが0の時用
