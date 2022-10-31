#pragma once
#include "Engine/GameObject.h"

class Door : public GameObject
{
	int hModel_;
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Draw() override;
};