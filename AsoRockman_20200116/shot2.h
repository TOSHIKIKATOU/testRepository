// AsoRockman
// 
// shot2.h
//
// 2019.12.13
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

void Shot2SystemInit(void);								// ¼®¯Äî•ñ‚Ì‰Šú‰»
void Shot2GameInit(void);								// ¼®¯Äî•ñ‚Ì¹Ş°Ñ‰Šú‰»
void Shot2Control(void);								// ¼®¯Ä‚Ì‘€ì
void Shot2GameDraw(void);								// ¼®¯Ä‚Ì•`‰æ
void CreateShot2(XY pPos, DIR pDir);					// ’e‚ğ¶¬‚·‚é
void DeleteShot2(void);									// ’e‚ğÁ–Å‚³‚¹‚é

bool Player2ShotHitCheck(XY sPos, XY sSize);			// 1P’e‚Æ2P’e‚Æ‚Ì“–‚½‚è”»’è (true:1P’e‚ª“–‚½‚Á‚½‚ç ,false:’e‚ªŠO‚ê‚½‚ç)ˆø” : ’e‚ÌÀ•W , ’e‚Ì‘å‚«‚³