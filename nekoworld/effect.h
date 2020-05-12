// AsoRockman
// 
// effect.h
//
// 2019.12.09
//
// 1916009_Kato Toshiki


// #pragma once


// 定数
//------------------------------------------------------------------
#define EFFECT_SIZE_MAX 6	// Effect用素材のｻｲｽﾞ種類
#define EFFECT_MAX 500		// Effect用素材の最大数
#define TOBICHIRI_EFFECT_MAX	200
#define PI            3.14592

enum EFFECT_COLOR {
	EFFECT_C_YELLOW,
	EFFECT_C_MAGENTA,
	EFFECT_C_CYAN,
	EFFECT_C_RED,
	EFFECT_C_BLACK,
	EFFECT_C_MAX
};

// エフェクトのタイプをEFFECT構造体に追加
enum EFFECT_TYPE {
	EFFECT_T_BLOCK,
	EFFECT_T_TOBICHIRI,
	EFFECT_T_MAX
};


struct EFFECT {
	EFFECT_TYPE effectType;	//エフェクトの種別
	int index;			//イメージの番号
	EFFECT_COLOR effectColor;	//エフェクトの色
	XY_F pos;				//座標
	XY_F move;			//移動量
	float speed;		//移動スピード
	float angle;		//移動角度
	XY size;			//画像のサイズ
	XY sizeOffset;		//画像補正量
	int life;			//エフェクトの寿命
	int lifeMax;		//寿命の最大
	bool visible;		//表示フラグ(True:表示)
};

struct EBICHIRI {
	XY_F pos;
	XY_F move;
};

// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//----------------------------------------------------------
bool EffectSystemInit(void);									// ｴﾌｪｸﾄの初期化用
void EffectGameInit(void);										// ｴﾌｪｸﾄのｹﾞｰﾑ用初期化用
void EffectControl(void);										// ｴﾌｪｸﾄの操作用
void EffectGameDraw(void);										// ｴﾌｪｸﾄの描画用

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor);			// ﾌﾞﾛｯｸに衝突したｴﾌｪｸﾄを設定

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor);		// ﾌﾞﾛｯｸ以外に衝突したｴﾌｪｸﾄ設定