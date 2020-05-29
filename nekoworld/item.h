//#pragma once
#define ITEM_MAX 50			//�ő�A�C�e����
#define SKANA_MAX 100	
#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 50
#define ITEM_BRAND 3



enum SKANA_TYPE
{
	SKANA_TYPE_A,
	SKANA_TYPE_B,
	SKANA_TYPE_C,
	SKANA_TYPE_MAX
};
enum ITEM_TYPE
{	
	ITEM_TYPE_NEKOKAN,			
	ITEM_TYPE_MATATABI,	
	ITEM_TYPE_MAX
};

bool ItemSystemInit(void);//�e�̏�����
void ItemGameInit(void);
void CreateItem(void);
void ItemControl(void);//�e�̑{��
void ItemDraw(void);//�e�̕`��
void Deleteitem(void);


//XY Pos22Index(XY pos);				// �߸�ٍ��W�n����ϯ�ߔz����W�n�ɕϊ�����B
//XY Index22Pos(XY index);				// ϯ�ߔz����W�n�����߸�ٍ��W�n�ɕϊ�����B
//bool Is2Pass(XY pos);				// �w�肵�����W���ʉ߉\����Ԃ��@true:�ʉ߂ł���