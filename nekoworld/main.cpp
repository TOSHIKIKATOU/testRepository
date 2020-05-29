// AsoRockman
// 
// main.cpp
//
// 2019.11.01
//
// 1916009_Kato Toshiki


#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "scene.h"
#include "stage.h"
#include "player.h"
#include "player2.h"
#include "shot.h"
#include "shot2.h"
#include "effect.h"
#include"item.h"



// �ϐ�
//--------------------------------------------------------------------------------------------
SCENE_ID sceneID;						// ���̼��ID
SCENE_ID scenePreID;					// ��O�̼��ID
int SceneCounter;		

int titleImage;
int gameoverImage;
int hitstartImage;
int winImage[2];
int drawImage;
int time;
int mtImage;
int logoRol;
float logoScl;
int aaaa;
int tlImage;
int catImage[4];
int haikei2image;
XY haikei1Pos;
XY haikeiturnPos;
int haikei1image;
int haikeiturnimage;
FILE_DATA fileData;
XY selectpos;
int selectflag;
int select2flag;
int seCNT;
int P1Image[4];
int P2Image[4];
// WinMain()
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//-----	����������
	if (!SystemInit())
	{
		
		return -1;
	}

	////----- �ް�ٰ��
	while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		

		ClsDrawScreen();	// ��ʏ���

		// ��ݶ����̏�����
		if (sceneID != scenePreID)
		{
			scenePreID = sceneID;
			SceneCounter = 0;
		}

		KeyCheck();

		// Ҳݏ���
		switch (sceneID)
		{

			// ������
		case SCENE_ID_INIT:
			
			InitScene();
			break;

			// ����
		case SCENE_ID_TITLE:
			// ��ʐ؂�ւ��̪��
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// �̪�ďI���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI���㏈��
					sceneID = SCENE_ID_SERECT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
		TitleScene();
			break;
		case SCENE_ID_SERECT:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// �̪�ďI���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI���㏈��
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameSerectScene();
			break;

			// �ް�
		case SCENE_ID_GAME:
			// ��ʐ؂�ւ��̪��
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {}// �̪�ďI���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI���㏈��
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
			GameScene();
			break;

			// �ްѵ��ް
		case SCENE_ID_GAMEOVER:
			// ��ʐ؂�ւ��̪��
			if (fadeIn)
			{
				if (!FadeInScreen(5)) 
				{
					fadeOut = false;
				}// �̪�ďI���㏈��
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �̪�ďI���㏈��
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}

			GameOverScene();
			break;

		}
		
		SceneCounter++;

		ScreenFlip(); // ����ʂ�\��ʂɏu�Ժ�߰
	}

	DxLib_End(); // DXײ���؂̏I������

	return 0;
}

// ���я�����
bool SystemInit(void)
{
	bool retFlag = true; // �֐��̖߂�l// ���[�J���ϐ�

	//----- ���я���
	SetWindowText("1916009_Kato Toshiki");
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	
	KeyInit();			// ���̏�����
	EffectInit();		// �̪�Ă̏�����

	if (!StageSystemInit()) return false;
	PlayerSystemInit();
	Player2SystemInit();
	ShotSystemInit();
	Shot2SystemInit();
	ItemSystemInit();
	if (!EffectSystemInit()) return false;

	//----- ���̨���̓o�^

	LoadDivGraph("image/run5.png", 4, 4, 1, 80, 80, catImage);
	titleImage = LoadGraph("image/title.png");
	if (titleImage == -1)
	{
		AST();
		retFlag = false;
	}

	hitstartImage = LoadGraph("image/hitstartkey.png");
	if (hitstartImage == -1)
	{
		AST();
		retFlag = false;
	}

	winImage[0] = LoadGraph("image/WIN1.png");
	if (winImage[0] == -1)
	{
		AST();
		retFlag = false;
	}

	winImage[1] = LoadGraph("image/WIN2.png");
	if (winImage[1] == -1)
	{
		AST();
		retFlag = false;
	}

	drawImage = LoadGraph("image/Draw.png");
	if (drawImage == -1)
	{
		AST();
		retFlag = false;
	}
	mtImage= LoadGraph("image/�܂�����.png");
	if (mtImage == -1)
	{
		AST();
		retFlag = false;
	}
	tlImage = LoadGraph("image/�^�C�g��.png");
	haikeiturnimage= LoadGraph("image/�w�i.png");
	haikei1image = LoadGraph("image/�w�i.png");
	haikei2image = LoadGraph("image/�w�i�u���v.png");
	LoadDivGraph("image/run6.png", 4, 4, 1, 80, 80, P1Image);
	LoadDivGraph("image/run7.png", 4, 4, 1, 80, 80, P2Image);
	//P2Image = LoadGraph("image/���n.png");
	//P3Image = LoadGraph("image/�Q��.png");
	//----- �ϐ�������
	SceneCounter = 0;
	sceneID = SCENE_ID_INIT;
	scenePreID = SCENE_ID_MAX;
	
	aaaa = 0;

	return true;
}

// �������p��ݗp
void InitScene(void)
{
	sceneID = SCENE_ID_TITLE;
	StageGameInit();
	ShotGameInit();
	Shot2GameInit();
	PlayerGameInit();
	Player2GameInit();
	EffectGameInit();
	ItemGameInit();
	time = 60;
	haikei1Pos = {0,0};
	haikeiturnPos = { SCREEN_SIZE_X,0 };
	logoRol = 0;
	logoScl = 0.0f;
	fileData.score = 0;
	fileData.hiScore = 0;
	selectpos = {0,0};
	selectflag=false;
	select2flag = false;
	seCNT=0;

}

// ���ټ�ݗp
void TitleScene(void)
{
	
	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}


	haikei1Pos.x -= 5;			// �w�i�̃X�N���[��

	if (haikei1Pos.x <= -SCREEN_SIZE_X)
	{
		haikei1Pos.x = SCREEN_SIZE_X;
	}

	


	haikeiturnPos.x -= 5;		//  ���]�����w�i�̃X�N���[��

	if (haikeiturnPos.x <= -SCREEN_SIZE_X)
	{
		haikeiturnPos.x = SCREEN_SIZE_X;
	}
	
	TitleDraw();
}

// ���ټ�݂̕`��
void TitleDraw(void)
{
	

	//DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", SceneCounter, true);
	// �w�i�摜�̕`��
	DrawGraph(haikei1Pos.x
		, 0
		, haikei1image, true);
	// ���]�����w�i�摜�̕`��
	DrawTurnGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);
	DrawGraph(200
		, SCREEN_SIZE_Y-170
		, catImage[(SceneCounter / 10 % 4)], true);
	DrawGraph(haikei1Pos.x, 0, haikei2image, true);
	DrawTurnGraph(haikeiturnPos.x, 0, haikei2image, true);
	//DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);

	//DrawGraph(0, 0, titleImage, true);
	DrawGraph(0, 0, tlImage, true);
	DrawGraph(300, 430, hitstartImage, true);

}
void GameSerectScene(void)
{
	
	GameSerectSceneDraw();
		
		if (selectflag == false)
		{
			if (selectpos.y < 100)
			{
				if (keyDownTrigger[KEY_ID_P2RIGHT])
				{
					selectpos.y += 50;
				}
			}
			if (selectpos.y > 0)
			{
				if (keyDownTrigger[KEY_ID_P2LEFT])
				{
					selectpos.y -= 50;
				}
			}
		}
		if (selectflag == true)
		{
			if (selectpos.x > 250)
			{
				if (keyDownTrigger[KEY_ID_P2LEFT])
				{
					selectpos.x -= 250;
				}
			}
			if (selectpos.x < 500)
			{
				if (keyDownTrigger[KEY_ID_P2RIGHT])
				{
					selectpos.x += 250;
				}
			}
		}
		DrawMenu();
		switch (selectpos.y)
		{
		case 0:	
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}
			break;
		case 50:
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}
			break;
		case 100:
			if (keyDownTrigger[KEY_ID_ENTER])
			{
				selectpos.x = 500;
				selectflag = !selectflag;
				fadeOut = true;
			}

			break;
		}

	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}
}
void GameSerectSceneDraw(void)
{
	// �w�i�摜�̕`��
	DrawGraph(haikei1Pos.x
		, 0
		, haikei1image, true);
	// ���]�����w�i�摜�̕`��
	DrawTurnGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);
	DrawGraph(haikei1Pos.x, 0, haikei2image, true);
	DrawTurnGraph(haikeiturnPos.x, 0, haikei2image, true);
	//DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);
}
void DrawMenu(void)
{
	if (selectpos.y == 0)
	{
		DrawBox(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);
		DrawExtendGraph(100, SCREEN_SIZE_Y / 2-100, 300, SCREEN_SIZE_Y/2+100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
		//DrawGraph(400, SCREEN_SIZE_Y / 2 - 50, P2Image, true);
		//DrawGraph(600, SCREEN_SIZE_Y / 2 - 50, P3Image, true);
	}
	else if (selectpos.y == 50)
	{
		DrawBox(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);

		DrawExtendGraph(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
	}
	else if (selectpos.y == 100)
	{

		DrawBox(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100, 0x0000FF, false);

		DrawExtendGraph(100, SCREEN_SIZE_Y / 2 - 100, 300, SCREEN_SIZE_Y / 2 + 100,
			catImage[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(350, SCREEN_SIZE_Y / 2 - 100, 550, SCREEN_SIZE_Y / 2 + 100,
			P1Image[(SceneCounter / 10 % 4)], true);
		DrawExtendGraph(600, SCREEN_SIZE_Y / 2 - 100, 800, SCREEN_SIZE_Y / 2 + 100,
			P2Image[(SceneCounter / 10 % 4)], true);
	}
}
// �ްѼ�ݗp
void GameScene(void)
{

	if (Player1Dawn() == true || Player2Dawn()  == true || time ==  0)
	{
		
		fadeOut = true;
	}

	// Pause�@�\
	if (keyUpTrigger[KEY_ID_PAUSE])
	{
		pauseFlag = !pauseFlag;
	}

	if (pauseFlag == true)
	{
		SetDrawBright(128, 128, 128);
	}
	else
	{
		aaaa++;	// �e�폈��
		DeleteShot();
		DeleteShot2();
		PlayerControl();
		Player2Control();
		/*StageGame();*/
		ShotControl();
		Shot2Control();
		EffectControl();
		ItemControl();
		Deleteitem();
		
		if (SceneCounter % 60 == 59)
		{
			time--;
		}
	}


	GameSceneDraw();

	if (pauseFlag == true)
	{
		SetDrawBright(255, 255, 255);
		DrawString(280 , 230, "�o�`�t�r�d", GetColor(255, 255, 255), true);
	}


	return;
}
// �ްѼ�݂̕`��
void GameSceneDraw(void)
{
	StageGameDraw();
	ShotGameDraw();

	Shot2GameDraw();
	PlayerGameDraw();
	ItemDraw();
	
	EffectGameDraw();
	DrawFormatString(0, 0, 0xFFFFFF, "%d", fileData.score);
	if (time >= 10)
	{
		SetFontSize(35);
		DrawFormatString(365, 0, GetColor(0, 0, 0), "%d", time);
	}
	else if (time <= 9)
	{
		SetFontSize(60);
		DrawFormatString(370, 0, GetColor(255, 0, 0), "%d", time);
	}

	//DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);
}

// �ްѵ��ް��ݗp
void GameOverScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	// �w�iү���ނ̉�]�ƕ`��
	logoRol += 6;
	if (logoRol >= 360) logoRol = 360;
	logoScl += 0.02f;
	if (logoScl > 1.0f) logoScl = 1.0f;

	GameOverDraw();
}

// �ްѵ��ް��݂̕`��
void GameOverDraw(void)
{

	GameSceneDraw();

	// ���ʂ����Ƃɕ`��
	if (Player1Dawn() == false && Player2Dawn() == true)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl,
			logoScl, (DX_PI_F / 180)*logoRol, winImage[0], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == false)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl
			, logoScl, (DX_PI_F / 180)*logoRol, winImage[1], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == true || time <= 0 )
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl
			, logoScl, (DX_PI_F / 180)*logoRol, drawImage, true);
	}

	//DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}


void AddScore(int point)
{
	fileData.score += point;
	if (fileData.hiScore < fileData.score)
	{
		fileData.hiScore = fileData.score;
	}
}
