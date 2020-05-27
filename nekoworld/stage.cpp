// AsoRockman
// 
// stage.cpp
//
// 1419.11.05
//
// 1916009_Kato Toshiki

#include "DxLib.h"
#include "main.h"
#include "stage.h"


// �ϐ�
//--------------------------------------------------------------------------------------------
int chipImage[13];
XY mapPos;
int haikeiimage;
XY haikeiPos;
int haikeiturnimage;
XY haikeiturnPos;
int haikeispeed;
int haikeicnt;


int map[MAP_Y][MAP_X] = {
{ 14, 14, 14, 14, 14, 14, 14, 14,	14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14,  14, 14, 14, 14, 14, 14, 14, 14 },
{ 14, 14, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20,  20, 20, 20, 20, 20, 20, 20, 20 },
};


// �ð�ޏ��̏�����
bool StageSystemInit(void)
{
	int ret;

	ret = LoadDivGraph("image/��Q��.png"
		, 14, 5, 4
		, CHIP_SIZE_X, CHIP_SIZE_X
		, chipImage);
	if (ret == -1)
	{
		AST();
		return false;
	}

	haikeiimage = LoadGraph("image/haikeiii.png");
	haikeiturnimage = LoadGraph("image/haikeiturn.png");

	haikeispeed = 1;
	haikeicnt = 0;

	return true;
}

// �ð�ޏ��̹ްя�����
void StageGameInit(void)
{

	// �ϐ��̏�����
	mapPos.x = 0;
	mapPos.y = 0;
	haikeiPos = { 0, 0};
	haikeiturnPos = { SCREEN_SIZE_X, 0 };
	haikeispeed = 1;
	haikeicnt = 0;

}

// �߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����B
XY Pos2Index(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;//pos��x���W��ϊ�;
	tmp.y = pos.y / CHIP_SIZE_Y;//pos��y���W��ϊ�;

								// �ϊ������l��Ԃ�
	return tmp;
}

// ϯ�ߔz����W�n�����߸�ٍ��W�n(����)�ɕϊ�����B
XY Index2Pos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;//pos��x���W��ϊ�;
	tmp.y = index.y * CHIP_SIZE_Y;//pos��y���W��ϊ�;

								// �ϊ������l��Ԃ�
	return tmp;
}

// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߂ł���
bool IsPass(XY pos)
{
	XY indexPos;

	indexPos = Pos2Index(pos);


	switch (map[indexPos.y][indexPos.x])
	{
	/*case 8:
	case 9:
	case 12:*/
	case 14:
		// �ʂ�Ȃ�
		return false;
		break;
	default:
		break;
	}
	return true;
	
}

// �ð�ނ̕`��
void StageGameDraw(void)
{
	haikeicnt++;

	if (haikeicnt % 1800 == 0)
	{
		haikeispeed++;
	}
		
	
	

	// �w�i�摜�̕`��
	DrawGraph(haikeiPos.x
		, 0
		, haikeiimage, true);

	// ���]�����w�i�摜�̕`��
	DrawGraph(haikeiturnPos.x
		, 0
		, haikeiturnimage, true);

	haikeiturnPos.x -= haikeispeed;		//  ���]�����w�i�̃X�N���[��

	haikeiPos.x -= haikeispeed;			// �w�i�̃X�N���[��

	if (haikeiPos.x <= -SCREEN_SIZE_X)
	{
		haikeiPos.x = haikeiturnPos.x + SCREEN_SIZE_X;
	}

	if (haikeiturnPos.x <= -SCREEN_SIZE_X)
	{
		haikeiturnPos.x = haikeiPos.x + SCREEN_SIZE_X;
	}

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X + -mapPos.x
				, y * CHIP_SIZE_Y + -mapPos.y
				, chipImage[map[y][x]], true);
		}
	}

}