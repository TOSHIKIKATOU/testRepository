// AsoRockman
// 
// effect.cpp
//
// 2019.12.09
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "main.h"
#include "effect.h"
#include "math.h"
#include "stage.h"


// 変数
//--------------------------------------------------------------------------------------------
int effectImage[EFFECT_C_MAX][EFFECT_SIZE_MAX];
EFFECT effect[EFFECT_MAX];

float tobichiriAcc;		//飛びちりの際の落下用加速度
EBICHIRI ebichiri[TOBICHIRI_EFFECT_MAX];
bool ballFlag;
float effectAcc;


// ｴﾌｪｸﾄの初期化用
bool EffectSystemInit(void)
{
	int ret;
	ret = LoadDivGraph("image/effect_yellow.png"
		, 6
		, 6
		, 1
		, 16
		, 16
		, effectImage[EFFECT_C_YELLOW],true);
	if (ret == -1)
	{
		AST();
		return false;
	}

	ret = LoadDivGraph("image/effect_magenta.png"
		, 1 * EFFECT_SIZE_MAX
		, EFFECT_SIZE_MAX
		, 1
		, 16
		, 16
		, effectImage[EFFECT_C_MAGENTA], true);
	if (ret == -1)
	{
		AST();
		return false;
	}

	ret = LoadDivGraph("image/effect_cyan.png"
		, 1 * EFFECT_SIZE_MAX
		, EFFECT_SIZE_MAX
		, 1
		, 16
		, 16
		, effectImage[EFFECT_C_CYAN], true);
	if (ret == -1)
	{
		AST();
		return false;
	}

	ret = LoadDivGraph("image/effect_red.png"
		, 1 * EFFECT_SIZE_MAX
		, EFFECT_SIZE_MAX
		, 1
		, 16
		, 16
		, effectImage[EFFECT_C_RED], true);
	if (ret == -1)
	{
		AST();
		return false;
	}

	ret = LoadDivGraph("image/effect_black.png"
		, 1 * EFFECT_SIZE_MAX
		, EFFECT_SIZE_MAX
		, 1
		, 16
		, 16
		, effectImage[EFFECT_C_BLACK], true);
	if (ret == -1)
	{
		AST();
		return false;
	}


	return true;
}

// ｴﾌｪｸﾄのｹﾞｰﾑ用初期化用
void EffectGameInit(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{

		effect[ef].index = 0;			//イメージの番号
		effect[ef].effectColor = EFFECT_C_YELLOW;	//エフェクトの色
		effect[ef].pos = { 0,0, };			//座標
		effect[ef].move = { 0,0 };			//移動量
		effect[ef].speed = 0.0;		//移動スピード
		effect[ef].angle = 0.0;		//移動角度
		effect[ef].size = {16,16};			//画像のサイズ
		effect[ef].sizeOffset = { effect[ef].size.x  / 2,effect[ef].size.y / 2 };		//画像補正量
		effect[ef].life = 0;			//エフェクトの寿命
										//effect[ef].lifeMax;		//寿命の最大
		effect[ef].visible = false;		//表示フラグ(True:表示)

		 
	}

	effectAcc = 0.0f;

}

// ｴﾌｪｸﾄの操作用
void EffectControl(void)
{
	effectAcc += 0.7;
	XY_F tempPos;
	XY tempIntPos;

	// ｴﾌｪｸﾄのﾙｰﾌﾟ
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (effect[ef].visible)
		{
			
			if (effectAcc > SCREEN_SIZE_Y) effectAcc = 0.0;
			tempPos = effect[ef].pos;
			tempPos.y += effectAcc;
			tempPos.x += (effect[ef].move.x);
			tempPos.y += (effect[ef].move.y);
			tempIntPos.x = (int)tempPos.x;
			tempIntPos.y = (int)tempPos.y;
			effect[ef].speed -= 0.1f;	// 少しずつ減速
			if (IsPass(tempIntPos))
			{
				
				if (SCREEN_SIZE_Y - CHIP_SIZE_Y > tempPos.y) effect[ef].pos = tempPos;
			}
			else
			{
				effect[ef].visible = false;
			}
		}
		effect[ef].life--;
		if (effect[ef].life == 0) effect[ef].visible = false;

	
	}
	
	
}

// ｴﾌｪｸﾄの描画用
void EffectGameDraw(void)
{

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		// trueの時だけ表示
		if (effect[ef].visible)
		{
			DrawGraph(effect[ef].pos.x - effect[ef].sizeOffset.x + -mapPos.x
				, effect[ef].pos.y - effect[ef].sizeOffset.y + -mapPos.y
				, effectImage[effect[ef].effectColor][GetRand(5)]
				, true);
		}
		
	}
	
}

// ﾌﾞﾛｯｸに衝突したｴﾌｪｸﾄを設定
void SetBlockEffect(XY pos, EFFECT_COLOR effectColor)
{
	//float rad;		// 角度
	//float speed;	// 素材のｽﾋﾟｰﾄﾞ

	int effectCount = 0;

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (!effect[ef].visible)
		{
			effectCount++;
			effect[ef].life = 30;

			// 1°ずつ動かしながら素材を生成する。

			// 素材の移動速度は乱数(1～10)を使って作る。
			// effect[ef].angle = GetRand(360.0);
			effect[ef].angle = ef * 3;	// 3度ずつ回転
			effect[ef].angle += 1 * PI / 180.0;
			effect[ef].speed = GetRand(900)/100.0; // 0～9.00　までの数

			effect[ef].pos.x = pos.x;
			effect[ef].pos.y = pos.y;
			effect[ef].move.x = effect[ef].speed * sin(effect[ef].angle);
			effect[ef].move.y = effect[ef].speed * cos(effect[ef].angle);

			effect[ef].index = 4;

			effect[ef].effectColor = effectColor;

			//effectAcc = 0.5;

			effect[ef].visible = true;

			if (effectCount > TOBICHIRI_EFFECT_MAX)
			{
				break;
			}
		}

		
	}
	
	effectAcc = 0.0;
}

// ﾌﾞﾛｯｸ以外に衝突したｴﾌｪｸﾄ設定
void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor)
{
	int effectCount = 0;

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (!effect[ef].visible)
		{
			effectCount++;
			effect[ef].life = 50;

			// 1°ずつ動かしながら素材を生成する。

			// 素材の移動速度は乱数(1～10)を使って作る。
			// effect[ef].angle = GetRand(360.0);
			effect[ef].angle = ef * 3;	// 3度ずつ回転
			effect[ef].angle += 1 * PI / 180.0;
			effect[ef].speed = GetRand(1400) / 100.0; // 0～14.00　までの数

			effect[ef].pos.x = pos.x;
			effect[ef].pos.y = pos.y;
			effect[ef].move.x = effect[ef].speed * sin(effect[ef].angle);
			effect[ef].move.y = effect[ef].speed * cos(effect[ef].angle);

			effect[ef].index = GetRand(5);

			// effectAcc = 0.7;

			effect[ef].effectColor = effectColor;

			effect[ef].visible = true;
			if (effectCount > TOBICHIRI_EFFECT_MAX)
			{
				break;
			}
			
		}


	}

	


	effectAcc = 0.0;
}