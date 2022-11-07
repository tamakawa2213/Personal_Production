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

class Screen_Room : public GameObject
{
	const struct DoorPos
	{
		XMFLOAT3 Door_H = XMFLOAT3(NULL, NULL, -4.0f);
		XMFLOAT3 Door_Lw = XMFLOAT3(NULL, NULL, 4.0f);
		XMFLOAT3 Door_Lt = XMFLOAT3(-4.0f, NULL, NULL);
		XMFLOAT3 Door_R = XMFLOAT3(4.0f, NULL, NULL);
	};

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
