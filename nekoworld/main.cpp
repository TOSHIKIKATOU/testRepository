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

int logoRol;
float logoScl;

int aaaa;

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
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);

				}
			}
		TitleScene();
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
	if (!EffectSystemInit()) return false;

	//----- ���̨���̓o�^

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

	time = 60;

	logoRol = 0;

	logoScl = 0.0f;
}

// ���ټ�ݗp
void TitleScene(void)
{
	
	if (keyUpTrigger[KEY_ID_SPACE])
	{

		fadeOut = true;

	}

	
	TitleDraw();
}

// ���ټ�݂̕`��
void TitleDraw(void)
{
	

	//DrawFormatString(0, 0, 0xFFFFFF, "TitleScene : %d", SceneCounter, true);

	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0),true);

	DrawGraph(0, 0, titleImage, true);

	DrawGraph(200, 430, hitstartImage, true);

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
		ShotControl();
		Shot2Control();
		EffectControl();
		
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

	Player2GameDraw();

	EffectGameDraw();

	//DrawFormatString(0, 0, 0xFFFFFF, "GameScene : %d", SceneCounter, true);


	//DrawFormatString(32, 32, 0xFFFFFF, " %d ", aaaa, true);

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
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, winImage[0], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == false)
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, winImage[1], true);
	}
	else if (Player1Dawn() == true && Player2Dawn() == true || time <= 0 )
	{
		DrawRotaGraph3(SCREEN_SIZE_X / 2, 240, 250, 50, logoScl, logoScl, (DX_PI_F / 180)*logoRol, drawImage, true);
	}

	//DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}



