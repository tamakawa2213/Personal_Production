#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class Pin : public GameObject
{
	int hModel_;
public:
	bool Disp_;				//表示の有無
	XMFLOAT2 UVPosition_;	//パズル画面上の位置

	Pin(GameObject* parent);

	~Pin();

	void Initialize() override;

	void Draw() override;

	void Release() override;
};