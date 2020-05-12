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


// �ϐ�
//--------------------------------------------------------------------------------------------
int effectImage[EFFECT_C_MAX][EFFECT_SIZE_MAX];
EFFECT effect[EFFECT_MAX];

float tobichiriAcc;		//��т���̍ۂ̗����p�����x
EBICHIRI ebichiri[TOBICHIRI_EFFECT_MAX];
bool ballFlag;
float effectAcc;


// �̪�Ă̏������p
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

// �̪�Ă̹ްїp�������p
void EffectGameInit(void)
{
	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{

		effect[ef].index = 0;			//�C���[�W�̔ԍ�
		effect[ef].effectColor = EFFECT_C_YELLOW;	//�G�t�F�N�g�̐F
		effect[ef].pos = { 0,0, };			//���W
		effect[ef].move = { 0,0 };			//�ړ���
		effect[ef].speed = 0.0;		//�ړ��X�s�[�h
		effect[ef].angle = 0.0;		//�ړ��p�x
		effect[ef].size = {16,16};			//�摜�̃T�C�Y
		effect[ef].sizeOffset = { effect[ef].size.x  / 2,effect[ef].size.y / 2 };		//�摜�␳��
		effect[ef].life = 0;			//�G�t�F�N�g�̎���
										//effect[ef].lifeMax;		//�����̍ő�
		effect[ef].visible = false;		//�\���t���O(True:�\��)

		 
	}

	effectAcc = 0.0f;

}

// �̪�Ă̑���p
void EffectControl(void)
{
	effectAcc += 0.7;
	XY_F tempPos;
	XY tempIntPos;

	// �̪�Ă�ٰ��
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
			effect[ef].speed -= 0.1f;	// ����������
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

// �̪�Ă̕`��p
void EffectGameDraw(void)
{

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		// true�̎������\��
		if (effect[ef].visible)
		{
			DrawGraph(effect[ef].pos.x - effect[ef].sizeOffset.x + -mapPos.x
				, effect[ef].pos.y - effect[ef].sizeOffset.y + -mapPos.y
				, effectImage[effect[ef].effectColor][GetRand(5)]
				, true);
		}
		
	}
	
}

// ��ۯ��ɏՓ˂����̪�Ă�ݒ�
void SetBlockEffect(XY pos, EFFECT_COLOR effectColor)
{
	//float rad;		// �p�x
	//float speed;	// �f�ނ̽�߰��

	int effectCount = 0;

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (!effect[ef].visible)
		{
			effectCount++;
			effect[ef].life = 30;

			// 1�����������Ȃ���f�ނ𐶐�����B

			// �f�ނ̈ړ����x�͗���(1�`10)���g���č��B
			// effect[ef].angle = GetRand(360.0);
			effect[ef].angle = ef * 3;	// 3�x����]
			effect[ef].angle += 1 * PI / 180.0;
			effect[ef].speed = GetRand(900)/100.0; // 0�`9.00�@�܂ł̐�

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

// ��ۯ��ȊO�ɏՓ˂����̪�Đݒ�
void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor)
{
	int effectCount = 0;

	for (int ef = 0; ef < EFFECT_MAX; ef++)
	{
		if (!effect[ef].visible)
		{
			effectCount++;
			effect[ef].life = 50;

			// 1�����������Ȃ���f�ނ𐶐�����B

			// �f�ނ̈ړ����x�͗���(1�`10)���g���č��B
			// effect[ef].angle = GetRand(360.0);
			effect[ef].angle = ef * 3;	// 3�x����]
			effect[ef].angle += 1 * PI / 180.0;
			effect[ef].speed = GetRand(1400) / 100.0; // 0�`14.00�@�܂ł̐�

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