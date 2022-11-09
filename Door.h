#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"

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

	float MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);	//行列をかけてマウスカーソルのレイを作る
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	
	void SetID(char ID);
	char GetID() { return DoorID_; }
};