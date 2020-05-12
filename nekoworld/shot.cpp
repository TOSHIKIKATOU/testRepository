// AsoRockman
// 
// shot.cpp
//
// 2019.11.21
//
// 1916009_Kato Toshiki

#include "Dxlib.h"
#include "main.h"
#include "shot.h"
#include "shot2.h"
#include "stage.h"
#include "keycheck.h"
#include "player.h"
#include "player2.h"
#include "effect.h"




// •Ï”
//-------------------------------------------------------------------
CHARACTER shot[SHOT_MAX];
int shotImage;
XY ShotPosHit[SHOT_MAX];


// ¼®¯Äî•ñ‚Ì‰Šú‰»
void ShotSystemInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		//shot[sh].chartype = ;							// ·¬×¸À‚Ìí—Ş
		shot[sh].moveDir = DIR_DOWN;					// ·¬×¸À‚ÌŒü‚«
		shot[sh].pos.x = 150;								// ·¬×¸À‚Ì’n}ã‚ÌXÀ•W
		shot[sh].pos.y = 150;								// ·¬×¸À‚Ì’n}ã‚ÌYÀ•W
		shot[sh].size.x = 16;							// ·¬×¸À‚ª‰æ‘œ‚Ì»²½Ş
		shot[sh].size.y = 16;							// ·¬×¸À‚ª‰æ‘œ‚Ì»²½Ş
		shot[sh].sizeOffset.x = shot[sh].size.x / 2;	// ·¬×¸À‚ÌµÌ¾¯Ä
		shot[sh].sizeOffset.y = shot[sh].size.y / 2;	// ·¬×¸À‚ÌµÌ¾¯Ä
		shot[sh].moveSpeed = SHOT_DEF_SPEED;							// ·¬×¸À‚ÌˆÚ“®½Ëß°ÄŞ
		shot[sh].life = 0;					// ·¬×¸À‚Ì‘Ì—ÍÅ‘å’l
		shot[sh].lifeMax = SHOT_LIFE_MAX;
		shot[sh].animCnt = 0;							// ·¬×¸À‚Ì±ÆÒ°¼®İ
		ShotPosHit[sh] = shot[sh].sizeOffset;
		shot[sh].imgLockCnt = 0;

	}

	

	shotImage = LoadGraph("image/shot1.png");


}

// ’e‚ğ¶¬‚·‚é
void CreateShot(XY pPos, DIR pDir)
{
	// ’e‚Ì”•ªŒ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚È‚¢‚©‚ğÁª¯¸‚µ
	// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚ê‚Îˆê”­’e‚ğ”­Ë‚·‚éB
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].imgLockCnt++;

		// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ğ’T‚·B
		if (shot[sh].life <= 0)
		{
			// Œ‚‚Á‚Ä‚¢‚È‚¢’e‚ª‚ ‚Á‚½‚Ì‚Å”­ËB
			// ’e‚ÌêŠ
			shot[sh].pos.x = pPos.x;
			shot[sh].pos.y = pPos.y + 6;
			// ’e‚Ìi‚Ş‚×‚«•ûŒü
			shot[sh].moveDir = pDir;
			// ’e‚ğŒ‚‚Á‚½‚±‚Æ‚É‚·‚é

			shot[sh].life = shot[sh].lifeMax;

			break;
		}

	}


}

// ¼®¯Äî•ñ‚Ì¹Ş°Ñ‰Šú‰»
void ShotGameInit(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		shot[sh].visible = false;
		shot[sh].moveSpeed = SHOT_DEF_SPEED;						// ·¬×¸À‚ÌˆÚ“®½Ëß°ÄŞ
		shot[sh].life = 0;								// ·¬×¸À‚Ì‘Ì—ÍÅ‘å’l
		shot[sh].animCnt = 0;							// ·¬×¸À‚Ì±ÆÒ°¼®İ

	}


}

// ¼®¯Ä‚Ì‘€ì
void ShotControl(void)
{
	

	// ’e‚ğ“®‚©‚·ˆ—
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		XY shotPosCopy = shot[sh].pos;
		XY shotPosOffset = shotPosCopy;

		shot[sh].animCnt++;
		// Œ‚‚Á‚Ä‚¢‚é’e‚ğ’T‚·
		if (shot[sh].life > 0)
		{
			switch (shot[sh].moveDir)
			{
			case DIR_RIGHT:
				// ’e‚ğˆÚ“®‚³‚¹‚éB
				shotPosCopy.x += shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;

			case DIR_LEFT:
				// ’e‚ğˆÚ“®‚³‚¹‚éB
				shotPosCopy.x -= shot[sh].moveSpeed;
				shotPosOffset.x = shotPosCopy.x;
				if (IsPass(shotPosOffset))
				{
					shot[sh].pos.x = shotPosCopy.x;
				}
				else
				{
					shot[sh].life = 0;
				}
				break;
			}

			// õ–½‚ğŒ¸‚ç‚·
			shot[sh].life--;


			if (!IsPass(shotPosOffset))
			{
				SetBlockEffect(shot[sh].pos, EFFECT_C_YELLOW);
			}
		}

	}

	


}

// ¼®¯Ä‚Ì•`‰æ
void ShotGameDraw(void)
{
	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			DrawGraph(shot[sh].pos.x - shot[sh].sizeOffset.x + -mapPos.x
				, shot[sh].pos.y - shot[sh].sizeOffset.y + -mapPos.y
				, shotImage
				, true);



		}


	}
}

// ’e‚ğÁ–Å‚³‚¹‚é
void DeleteShot(void)
{
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{
		if (shot[sh].life > 0)
		{


			if (Player2HitCheck(shot[sh].pos, shot[sh].size))shot[sh].life = 0;

			/*if (Player2ShotHitCheck(shot[sh].pos, shot[sh].size))
			{
				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				
			}*/
		}

	}



}

// 1P’e‚Æ2P’e‚Æ‚Ì“–‚½‚è”»’è (true:1P’e‚ª“–‚½‚Á‚½‚ç ,false:’e‚ªŠO‚ê‚½‚ç)ˆø” : ’e‚ÌÀ•W , ’e‚Ì‘å‚«‚³
bool Player1ShotHitCheck(XY sPos, XY sSize)
{
	// ‘S‚Ä‚Ì“G‚É“–‚½‚è”»’è‚ğÀ{‚·‚é
	
	

	for (int sh = 0; sh < SHOT_MAX; sh++)
	{

		if (shot[sh].life > 0)
		{
			// “–‚½‚è‚Í”»’è•û–@‚Í©—R (‹éŒ`‚Å‚à—Ç‚¢‚µA“_‚Æ‚Ì‹——£‚Å‚à‚æ‚¢B)
			if (((shot[sh].pos.x - shot[sh].size.x / 2) < (sPos.x + sSize.x / 2))
				&& ((shot[sh].pos.x + shot[sh].size.x / 2) > (sPos.x - sSize.x / 2))
				&& ((shot[sh].pos.y - shot[sh].size.y / 2) < (sPos.y + sSize.y / 2))
				&& ((shot[sh].pos.y + shot[sh].size.y / 2) > (sPos.y - sSize.y / 2)))
			{
				// “–‚½‚Á‚½

				SetTobichiriEffect(shot[sh].pos, EFFECT_C_RED);

				shot[sh].life = 0;

				return true;
			}
		}
		

	}


	return false;

}
