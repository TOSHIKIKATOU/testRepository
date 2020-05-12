// AsoRockman
// 
// effect.h
//
// 2019.12.09
//
// 1916009_Kato Toshiki


// #pragma once


// �萔
//------------------------------------------------------------------
#define EFFECT_SIZE_MAX 6	// Effect�p�f�ނ̻��ގ��
#define EFFECT_MAX 500		// Effect�p�f�ނ̍ő吔
#define TOBICHIRI_EFFECT_MAX	200
#define PI            3.14592

enum EFFECT_COLOR {
	EFFECT_C_YELLOW,
	EFFECT_C_MAGENTA,
	EFFECT_C_CYAN,
	EFFECT_C_RED,
	EFFECT_C_BLACK,
	EFFECT_C_MAX
};

// �G�t�F�N�g�̃^�C�v��EFFECT�\���̂ɒǉ�
enum EFFECT_TYPE {
	EFFECT_T_BLOCK,
	EFFECT_T_TOBICHIRI,
	EFFECT_T_MAX
};


struct EFFECT {
	EFFECT_TYPE effectType;	//�G�t�F�N�g�̎��
	int index;			//�C���[�W�̔ԍ�
	EFFECT_COLOR effectColor;	//�G�t�F�N�g�̐F
	XY_F pos;				//���W
	XY_F move;			//�ړ���
	float speed;		//�ړ��X�s�[�h
	float angle;		//�ړ��p�x
	XY size;			//�摜�̃T�C�Y
	XY sizeOffset;		//�摜�␳��
	int life;			//�G�t�F�N�g�̎���
	int lifeMax;		//�����̍ő�
	bool visible;		//�\���t���O(True:�\��)
};

struct EBICHIRI {
	XY_F pos;
	XY_F move;
};

// �������ߐ錾
//----------------------------------------------------------
bool EffectSystemInit(void);									// �̪�Ă̏������p
void EffectGameInit(void);										// �̪�Ă̹ްїp�������p
void EffectControl(void);										// �̪�Ă̑���p
void EffectGameDraw(void);										// �̪�Ă̕`��p

void SetBlockEffect(XY pos, EFFECT_COLOR effectColor);			// ��ۯ��ɏՓ˂����̪�Ă�ݒ�

void SetTobichiriEffect(XY pos, EFFECT_COLOR effectColor);		// ��ۯ��ȊO�ɏՓ˂����̪�Đݒ�