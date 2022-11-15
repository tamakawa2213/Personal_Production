#pragma once
#include "Engine/Model.h"
#include "IDObject.h"

enum
{
	DOOR_ID_H,
	DOOR_ID_LW,
	DOOR_ID_LT,
	DOOR_ID_R
};

class Door : public IDObject
{
	int hModel_;
	bool RayHit_;

	float MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);	//行列をかけてマウスカーソルのレイを作る

	void SendtoPlayer();				//PlayerクラスにIDを送る
public:
	Door(GameObject* parent);
	~Door();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};