#pragma once
#include "Engine/GameObject.h"

enum
{
	Room_HLt,
	Room_HR,
	Room_LwLt,
	Room_LwR,
	Room_LtR,
	Room_MAX		//•”‰®‚Ìí—Ş‚ÌÅ‘å’l
};

class Screen_Room : public GameObject
{
	int hModel_[Room_MAX];

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
};
