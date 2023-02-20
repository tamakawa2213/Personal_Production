#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include "IDObject.h"

class Door;

class Screen_Room : public IDObject
{
	static const char DoorNum = 2;

	int hModel_;

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
};
