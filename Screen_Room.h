#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"
#include "IDObject.h"

class Door;

class Screen_Room : public IDObject
{
	static const char DoorNum = 2;

	int hModel_;

	char RoomType_;		//�����̃^�C�v

	short PrevPosX_;	//���O�̈ʒu
	short PrevPosY_;

	void Look_Around();	//���_���ړ�������

	Door* pDoor[DoorNum];
public:
	Screen_Room(GameObject* parent);

	~Screen_Room();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	//�����̈ړ��Ə�����
	void MoveOther(char Type);
};
