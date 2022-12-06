#pragma once
#include "Engine/GameObject.h"

#define BoardSize_  4		//���E�c���ꂼ��̑傫��
#define Empty_ -1			//�󔒂̃}�X
#define TIMETOMOVE 60		//�ړ��ɂ����鎞��
#define BOARDTOTAL_ 16		//�Ֆʂ̃}�X�̑���

class Player;

struct DoorPath	//�ʂ��h�A���r�b�g�Ŏ���(��A���A�E�A���̏�)
{
	const char DoorH = 0x08;
	const char DoorLw = 0x04;
	const char DoorLt = 0x02;
	const char DoorR = 0x01;
};

struct Move
{
	int moveHLw;
	int moveLtR;
};

const Move Direction[4]
{
	{1,0},		//��
	{-1,0},		//��
	{0,-1},		//��
	{0,1}		//�E
};

enum
{
	Board_HLt,
	Board_HR,
	Board_LwLt,
	Board_LwR,
	Board_LtR,
	Board_MAX		//�{�[�h�̎�ނ̍ő�l
};

class Screen_Puzzle : public GameObject
{
	char PuzX_;
	char PuzZ_;
	int hModel_[Board_MAX];	//�i�[���ꂽ�I�u�W�F�N�g�ԍ�
	int Board_[BoardSize_][BoardSize_];	//�{�[�h�̃f�[�^

	const char UnderSide = 8;	//�{�[�h�̉�����
	const char RightSide = 2;	//�{�[�h�̉E����
	int SeedData_;		//���̒l����Ƀp�Y���̔Ֆʂ𐶐�

	bool Wait_;			//�ҋ@���Ԃ��ǂ���

	char Mode_;			//��Փx�w��

	char Moving_;		//�ړ����J�n���Ă���o�߂����t���[�������L�^
	char MovingPanel_;	//�ړ����̃}�X�̒l������
	char MoveDir_;		//�ړ��������

	void AssignPuzzle();					//�����n�̃p�Y���Ֆʂ��쐬
	void Shuffle();							//�p�Y���������_���ɐ�������
	void AssignGoal();						//�S�[���̈ʒu�𐶐�

	Player* pPlayer_;

	void Swap(int x, int z);				//�󔒂ɗׂ荇���Ă���Ό�������
	void PrickPin();						//�s���h��

	bool MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);		//�s��������ă}�E�X�J�[�\���̃��C�����

	bool DoorConfig(char BoardType, char DoorID);	//�������h�A����ׂ荇�������Ɉړ��ł��邩

	void Moving();	//�����Ă���̑ҋ@����
public:
	Screen_Puzzle(GameObject* parent);

	~Screen_Puzzle();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	char SendToken(XMFLOAT2 pPos, char DoorID);	//Player�Ɉړ��ł��邩�ǂ�����Ԃ�
};

