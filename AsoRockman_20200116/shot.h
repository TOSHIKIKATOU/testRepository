// AsoRockman
// 
// shot.h
//
// 2019.11.21
//
// 1916009_Kato Toshiki

//#pragma once

// ’è”
//------------------------------------------------------------------
#define SHOT_MAX 50
#define SHOT_DEF_SPEED  12
#define SHOT_LIFE_MAX 40

#define SHOT2_MAX 50
#define SHOT2_DEF_SPEED  12
#define SHOT2_LIFE_MAX 40

// externéŒ¾
//-------------------------------------------------------------------
// extern CHARACTER shot[SHOT_MAX];

// ÌßÛÄÀ²ÌßéŒ¾
//---------------------------------------------------------------------

void ShotSystemInit(void);								// ¼®¯Äî•ñ‚Ì‰Šú‰»
void ShotGameInit(void);								// ¼®¯Äî•ñ‚Ì¹Ş°Ñ‰Šú‰»
void ShotControl(void);									// ¼®¯Ä‚Ì‘€ì
void ShotGameDraw(void);								// ¼®¯Ä‚Ì•`‰æ
void CreateShot(XY pPos, DIR pDir);						// ’e‚ğ¶¬‚·‚é
void DeleteShot(void);									// ’e‚ğÁ–Å‚³‚¹‚é

bool Player1ShotHitCheck(XY sPos, XY sSize);			// 1P’e‚Æ2P’e‚Æ‚Ì“–‚½‚è”»’è (true:1P’e‚ª“–‚½‚Á‚½‚ç ,false:’e‚ªŠO‚ê‚½‚ç)ˆø” : ’e‚ÌÀ•W , ’e‚Ì‘å‚«‚³