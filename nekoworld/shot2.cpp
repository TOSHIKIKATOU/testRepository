// AsoRockman
// 
// shot2.cpp
//
// 2019.12.13
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot2.h"
#include "shot.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// •Ï”
//-------------------------------------------------------------------


CHARACTER shot2[SHOT_MAX];
int shot2Image;
XY Shot2PosHit[SHOT_MAX];



// ¼®¯Äî•ñ‚Ì‰Šú‰»
void Shot2SystemInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ·¬×¸À‚Ìí—Ş
		shot2[sh].moveDir = DIR_DOWN;					// ·¬×¸À‚ÌŒü‚«
		shot2[sh].pos.x = 100;								// ·¬×¸À‚Ì’n}ã‚ÌXÀ•W
		shot2[sh].pos.y = 100;								// ·¬×¸À‚Ì’n}ã‚ÌYÀ•W
		shot2[sh].size.x = 16;							// ·¬×¸À‚ª‰æ‘œ‚Ì»²½Ş
		shot2[sh].size.y = 16;							// ·¬×¸À‚ª‰æ‘œ‚Ì»²½Ş
		shot2[sh].sizeOffset.x = shot2[sh].size.x / 2;	// ·¬×¸À‚ÌµÌ¾¯Ä
		shot2[sh].sizeOffset.y = shot2[sh].size.y / 2;	// ·¬×¸À‚ÌµÌ¾¯Ä
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;							// ·¬×¸À‚ÌˆÚ“®½Ëß°ÄŞ
		shot2[sh].life = 0;					// ·¬×¸À‚Ì‘Ì—ÍÅ‘å’l
		shot2[sh].lifeMax = SHOT2_LIFE_MAX;
		shot2[sh].animCnt = 0;							// ·¬×¸À‚Ì±ÆÒ°¼®İ
		Shot2PosHit[sh] = shot2[sh].sizeOffset;
		shot2[sh].imgLockCnt = 0;


	}

	shot2Image = LoadGraph("image/shot2.png");


}



// ’e‚ğ¶¬‚·‚é
void CreateShot2(XY pPos, DIR pDir)
{
	// ’e‚Ì”•ªŒ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚È‚¢‚©‚ğÁª¯¸‚µ
	// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚ê‚Îˆê”­’e‚ğ”­Ë‚·‚éB

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].imgLockCnt++;

		// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ğ’T‚·B
		if (shot2[sh].life <= 0)
		{
			// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚Á‚½‚Ì‚Å”­ËB
			// ’e‚ÌêŠ
			shot2[sh].pos.x = pPos.x;
			shot2[sh].pos.y = pPos.y + 6;
			// ’e‚Ìi‚Ş‚×‚«•ûŒü
			shot2[sh].moveDir = pDir;
			// ’e‚ğŒ‚‚Á‚½‚±‚Æ‚É‚·‚é

			shot2[sh].life = shot2[sh].lifeMax;

			break;
		}


	}
}

// ¼®¯Äî•ñ‚Ì¹Ş°Ñ‰Šú‰»
void Shot2GameInit(void)
{

	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		shot2[sh].visible = false;
		shot2[sh].moveSpeed = SHOT2_DEF_SPEED;						// ·¬×¸À‚ÌˆÚ“®½Ëß°ÄŞ
		shot2[sh].life = 0;								// ·¬×¸À‚Ì‘Ì—ÍÅ‘å’l
		shot2[sh].animCnt = 0;							// ·¬×¸À‚Ì±ÆÒ°¼®İ
	}
}

// ¼®¯Ä‚Ì‘€ì
void Shot2Control(void)
{

	// ’e‚ğ“®‚©‚·ˆ—
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{

		shot2[sh].animCnt++;
		// Œ‚‚Á‚Ä‚¢‚é’e‚ğ’T‚·
		if (shot2[sh].life > 0)
		{
			switch (shot2[sh].moveDir)
			{
			case DIR_RIGHT:
				// ’e‚ğˆÚ“®‚³‚¹‚éB
				shot2[sh].pos.x += shot2[sh].moveSpeed;
				break;

			case DIR_LEFT:
				// ’e‚ğˆÚ“®‚³‚¹‚éB
				shot2[sh].pos.x -= shot2[sh].moveSpeed;
				break;
			}

			// õ–½‚ğŒ¸‚ç‚·

			shot2[sh].life--;


			if (!IsPass(shot2[sh].pos))
			{
				shot2[sh].life = 0;
				SetBlockEffect(shot2[sh].pos, EFFECT_C_MAGENTA);
			}
		}

	}


}

// ¼®¯Ä‚Ì•`‰æ
void Shot2GameDraw(void)
{


	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{
			DrawGraph(shot2[sh].pos.x - shot2[sh].sizeOffset.x + -mapPos.x
				, shot2[sh].pos.y - shot2[sh].sizeOffset.y + -mapPos.y
				, shot2Image
				, true);
		}
	}



}



// ’e‚ğÁ–Å‚³‚¹‚é
void DeleteShot2(void)
{
	for (int sh = 0; sh < SHOT2_MAX; sh++)
	{
		if (shot2[sh].life > 0)
		{


			if (Player1HitCheck(shot2[sh].pos, shot2[sh].size)) shot2[sh].life = 0;

			if (Player1ShotHitCheck(shot2[sh].pos, shot2[sh].size))
			{
				SetTobichiriEffect(shot2[sh].pos, EFFECT_C_CYAN);

				shot2[sh].life = 0;
			}



		}
	}



}


