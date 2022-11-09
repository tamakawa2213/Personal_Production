#pragma once
#include "Engine/GameObject.h"

class Door : public GameObject
{
	enum
	{
		DOOR_ID_H,
		DOOR_ID_LW,
		DOOR_ID_LT,
		DOOR_ID_R
	};

	int hModel_;
	bool RayHit_;
	char DoorID_;
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	
	void SetID(char ID);
	char GetID() { return DoorID_; }
};