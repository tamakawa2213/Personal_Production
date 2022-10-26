#pragma once
#include "Engine/GameObject.h"

class Player : public GameObject
{
public:
	Player(GameObject* parent);

	~Player();

	void Initialize() override;

	void Update() override;

	void Release() override;
};