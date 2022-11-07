#pragma once
#include "Engine/GameObject.h"

class Door : public GameObject
{
	int hModel_;
	bool RayHit_;
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};