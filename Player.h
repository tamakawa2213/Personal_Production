#pragma once
#include "IDObject.h"

class Player : public IDObject
{
	XMFLOAT2 UVPosition_;
public:
	Player(GameObject* parent);

	~Player();

	void Initialize() override;

	void Update() override;

	void Release() override;

	void ReceiveFromDoor();
};