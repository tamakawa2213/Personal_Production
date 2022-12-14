#pragma once
#include "IDObject.h"

class Player : public IDObject
{
	XMFLOAT2 UVPosition_;	//パズル画面上の位置

	bool Wait_;				//待機状態かどうか

public:
	Player(GameObject* parent);

	~Player();

	void Initialize() override;

	void Update() override;

	void Release() override;

	void ReceiveFromDoor();

	XMFLOAT2 GetUVPos() { return UVPosition_; }
	void SetUVPos(XMFLOAT2 move);

	bool GetWait() { return Wait_; }
	void SetWait(bool wait);
};