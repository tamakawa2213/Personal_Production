#pragma once
#include "Engine/GameObject.h"
#include "IDObject.h"

#define DoorNum 2

class Door;

enum
{
	Room_HLt,
	Room_HR,
	Room_LwLt,
	Room_LwR,
	Room_LtR,
	Room_MAX		//部屋の種類の最大値
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
//ドアの配置
const char DoorConfig[Room_MAX] = { 0x0a, 0x09, 0x06, 0x05, 0x03 };

const char POSITION[POSITION_MAX] = { 0x08, 0x04, 0x02, 0x01 };

//ドアの位置
const XMFLOAT3 DoorPos[POSITION_MAX] =
{
	XMFLOAT3(NULL, NULL, -4.0f),
	XMFLOAT3(NULL, NULL, 4.0f),
	XMFLOAT3(-4.0f, NULL, NULL),
	XMFLOAT3(4.0f, NULL, NULL)
};

class Screen_Room : public IDObject
{
	int hModel_[Room_MAX];

	char RoomType_;		//部屋のタイプ

	short PrevPosX_;	//直前の位置
	short PrevPosY_;

	void Look_Around();	//視点を移動させる

	Door* pDoor[DoorNum];
public:
	Screen_Room(GameObject* parent);

	~Screen_Room();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	//部屋の移動と初期化
	void MoveOther(char Type);

	void SendIdInfo(char ID);
};
