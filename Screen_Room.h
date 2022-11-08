#pragma once
#include "Engine/GameObject.h"

#define DoorNum 2

enum
{
	Room_HLt,
	Room_HR,
	Room_LwLt,
	Room_LwR,
	Room_LtR,
	Room_MAX		//�����̎�ނ̍ő�l
};

enum
{
	HIGH,
	LOW,
	LEFT,
	RIGHT,
	POSITION_MAX
};

//H = 8, Lw = 4, Lt = 2, R = 1
//�h�A�̔z�u
const char DoorConfig[Room_MAX] = { 0x0a, 0x09, 0x06, 0x05, 0x03 };

const char POSITION[POSITION_MAX] = { 0x08, 0x04, 0x02, 0x01 };

const XMFLOAT3 DoorPos[POSITION_MAX] =
{
	XMFLOAT3(NULL, NULL, -4.0f),
	XMFLOAT3(NULL, NULL, 4.0f),
	XMFLOAT3(-4.0f, NULL, NULL),
	XMFLOAT3(4.0f, NULL, NULL)
};

class Screen_Room : public GameObject
{
	int hModel_[Room_MAX];

	char RoomType_;

	short PrevPosX_;
	short PrevPosY_;

	void Look_Around();
public:
	Screen_Room(GameObject* parent);

	~Screen_Room();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void MoveOther(char Type);
};