#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class Player;
class Screen_Puzzle;

class Goal : public GameObject
{
	int hModel_;
	bool RayHit_;						//レイが当たっているかどうか

	bool IsMouse_[2];					//マウスを押した瞬間と離した瞬間

	XMFLOAT2 UVPosition_;				//パズル画面上の位置

	Player* pPlayer_;

	void InitialPosition(char pos);		//初期位置を生成する
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