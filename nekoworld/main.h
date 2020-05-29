// AsoRockman
// 
// main.h
//
// 201911.01
//
// 1916009_Kato Toshiki

//#pragma once

//ｱｻｰﾄの定義
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "アサート表示", MB_OK);\
	}
#else
#define AST()
#endif


// 定数
//------------------------------------------------------------------
#define SCREEN_SIZE_X	960
#define SCREEN_SIZE_Y	480
#define ACC_G			7	// 重力加速度
#define FRAME_TIME		0.3f	// [s]
#define MUTEKI_TIME 80

// 列挙型の定義
//------------------------------------------------------------------
// ｼｰﾝ管理用
enum SCENE_ID
{
	SCENE_ID_INIT,			// 初期化ｼｰﾝ
	SCENE_ID_TITLE,			// ﾀｲﾄﾙｼｰﾝ
	SCENE_ID_SERECT,
	SCENE_ID_GAME,			// ｹﾞｰﾑｼｰﾝ
	SCENE_ID_GAMEOVER,		// ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
	SCENE_ID_MAX,
};

// ﾌﾟﾚｲﾔｰ管理用
enum PLAYER {
	PLAYER1
	, PLAYER2
	, PLAYER_MAX
};

enum DIR {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT,
	DIR_MAX
};

struct XY {
	int x;
	int y;
};

struct XY_F {
	float x;
	float y;
};

struct FILE_DATA
{
	int score;
	int hiScore;
};

struct CHARACTER {
	DIR moveDir;	//向いている方向
	XY pos;			//キャラクタの位置（中心）
	XY size;		//キャラクタ画像のサイズ
	XY sizeOffset;		//キャラクタ中央からの左上位置
	XY hitPosS;		//当たり判定用の左上
	XY hitPosE;		//当たり判定用の右下
	bool runFlag;		//キャラクタの状態（走っているか？）
	bool jumpFlag;		//キャラクタの状態（ジャンプしているか？）
	bool shotFlag;		//キャラクタの状態（弾撃っているか？）
	bool damageFlag;	//キャラクタの状態（ダメージ受けているか？）
	XY_F velocity;		// ｷｬﾗｸﾀの速度
	int moveSpeed;		//キャラクタの移動量
	int life;		//キャラクタの体力
	int lifeMax;		//キャラクタの体力最大
	int animCnt;		//キャラクタのアニメーション用カウンタ
	int imgLockCnt;		//キャラクタのイメージ固定用カウンタ
	bool visible;		//表示状態
	int type;			//何らかの属性を格納できる。
	int chartype;
	int point;
	XY ipos;
	int aniCnt;
};



// ﾌﾟﾛﾄﾀｲﾌﾟ宣言
//------------------------------------------------------------------
bool SystemInit(void);							// ｼｽﾃﾑ初期化
void InitScene(void);							// 初期化用ｼｰﾝ用
// ﾀｲﾄﾙｼｰﾝ
void TitleScene(void);							// ﾀｲﾄﾙｼｰﾝ用
void TitleDraw(void);							// ﾀｲﾄﾙｼｰﾝの描画
//ｹﾞｰﾑｾﾚｸﾄｼｰﾝ
void GameSerectScene(void);							// ｹﾞｰﾑｾﾚｸﾄｼｰﾝ用
void GameSerectSceneDraw(void);						// ｹﾞｰﾑｾﾚｸﾄｼｰﾝの描画
// ｹﾞｰﾑｼｰﾝ
void GameScene(void);							// ｹﾞｰﾑｼｰﾝ用
void GameSceneDraw(void);						// ｹﾞｰﾑｼｰﾝの描画
// ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ
void GameOverScene(void);						// ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝ用
void GameOverDraw(void);						// ｹﾞｰﾑｵｰﾊﾞｰｼｰﾝの描画
void AddScore(int point);

void DrawMenu(void);
