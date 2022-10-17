#pragma once
#include "Engine/GameObject.h"

class Screen_Room : public GameObject
{
public:
	Screen_Room(GameObject* parent);

	~Screen_Room();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};
