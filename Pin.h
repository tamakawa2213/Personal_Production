#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class Pin : public GameObject
{
	int hModel_;
public:
	bool Disp_;				//�\���̗L��
	XMFLOAT2 UVPosition_;	//�p�Y����ʏ�̈ʒu

	Pin(GameObject* parent);

	~Pin();

	void Initialize() override;

	void Draw() override;

	void Release() override;
};