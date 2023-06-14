#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include <vector>

static const int BoardSize_ = 4;		//���E�c���ꂼ��̑傫��

class Player;
enum class Difficulty;

enum class Board
{
	HLt = 0,
	HR,
	LwLt,
	LwR,
	LtR,
	MAX		//�{�[�h�̎�ނ̍ő�l
};

class Screen_Puzzle : public GameObject
{
	char PuzX_;
	char PuzZ_;
	int hModel_[(char)Board::MAX];	//�i�[���ꂽ�I�u�W�F�N�g�ԍ�
	int Board_[BoardSize_][BoardSize_];	//�{�[�h�̃f�[�^
	char GoalPos_;

	int SeedData_;		//���̒l����Ƀp�Y���̔Ֆʂ𐶐�
	std::vector<char> DecidedData_;		//����ς݃f�[�^

	bool Wait_;			//�ҋ@���Ԃ��ǂ���

	Difficulty Mode_;			//��Փx�w��

	char Moving_;		//�ړ����J�n���Ă���o�߂����t���[�������L�^
	char MovingPanel_;	//�ړ����̃}�X�̒l������
	char MoveDir_;		//�ړ��������

	void AssignPuzzle();					//�����n�̃p�Y���Ֆʂ��쐬
	void Shuffle();							//�p�Y���������_���ɐ�������
	void AssignGoal();						//�S�[���̈ʒu�𐶐�

	Player* pPlayer_;

	void Swap(int x, int z);				//�󔒂ɗׂ荇���Ă���Ό�������
	void PrickPin();						//�s���h��

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

