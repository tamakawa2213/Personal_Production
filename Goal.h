#pragma once
#include "Engine/Model.h"
#include "Engine/GameObject.h"
#include "Screen_Puzzle.h"

class Goal : public GameObject
{
	int hModel_;
	bool RayHit_;						//レイが当たっているかどうか

	bool IsMouse_[2];					//マウスを押した瞬間と離した瞬間

	XMFLOAT2 UVPosition_;				//パズル画面上の位置

	void InitialPosition(char pos);		//初期位置を生成する
	float MakeMouseRay();
	XMVECTOR SetInvMat(XMFLOAT3 pos);	//行列をかけてマウスカーソルのレイを作る
public:
	friend Screen_Puzzle;

	Goal(GameObject* parent);
	~Goal();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	XMFLOAT2 GetUVPos() { return UVPosition_; }
	void SetUVPos(XMFLOAT2 move);
};