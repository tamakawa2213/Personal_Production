#pragma once
#include "Engine/GameObject.h"

//GameObject�N���X���g������IDObject�N���X
class IDObject : public GameObject
{
	char IDData_;
public:
	IDObject(GameObject* parent);
	IDObject(GameObject* parent, std::string name);
	~IDObject();
	void SetID(char ID);
	char GetID() { return IDData_; }
};