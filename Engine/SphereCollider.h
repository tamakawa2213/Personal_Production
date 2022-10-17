#pragma once
#include "Transform.h"

class GameObject;

class SphereCollider
{
	float Radius_;				//���a
	GameObject* pGameObject_;	//GameObject�^�̃|�C���^
public:
	SphereCollider(XMFLOAT3 position, float Radius);
	~SphereCollider();

	bool Ishit(SphereCollider* pTarget);	//�Ăяo�����ƈ����Ɏ󂯎��������̓����蔻������s����

	float GetRadius() { return Radius_; }

	void SetGameObject(GameObject* obj) { pGameObject_ = obj; }
};