// AsoRockman
// 
// player.h
//
// 2019.11.05
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

extern CHARACTER player1;

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//------------------------------------------------------------------
void PlayerSystemInit(void);						// ﾌﾟﾚｲﾔｰ1情報の初期化
void PlayerGameInit(void);							// ﾌﾟﾚｲﾔｰ1情報のｹﾞｰﾑ初期化
void PlayerControl(void);							// ﾌﾟﾚｲﾔｰ1の操作
void PlayerGameDraw(void);							// ﾌﾟﾚｲﾔｰ1の描画

bool Player1HitCheck(XY sPos, XY sSize);			// player1とplayer2との当たり判定 (true:自機が当たったら ,false:弾が外れたら)引数 : 弾の座標 , 弾の大き

bool Player1Dawn(void);								// ﾌﾟﾚｲﾔｰ1のﾗｲﾌが0の時用