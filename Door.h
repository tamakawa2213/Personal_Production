#pragma once
#include "IDObject.h"

class Door : public IDObject
{
	int hModel_;
	bool RayHit_;						//レイが当たっているかどうか

	bool IsMouse_[2];					//マウスを押した瞬間と離した瞬間

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