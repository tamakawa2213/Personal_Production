#include <math.h>
#include "GameObject.h"

GameObject::GameObject() : childList_(), transform_(), pParent_(nullptr), objectName_(""), KILL(false), Collision_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const std::string& name) : childList_(), transform_(), pParent_(parent), objectName_(name), KILL(false), Collision_(nullptr)
{
	if (parent)
	{
		transform_.pParent_ = &parent->transform_;
	}
}

GameObject::~GameObject()
{
	Colliderlist_.clear();
}

void GameObject::UpdateSub()
{
	Update();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->UpdateSub();
	}

	for (auto itr = childList_.begin(); itr != childList_.end();) {
		if ((*itr)->KILL) {
			(*itr)->ReleaseSub();
			SAFE_DELETE(*itr);
			itr = childList_.erase(itr);
		}
		else {
			(*itr)->Collision(GetRootJob());
			itr++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	Release();

	for (auto itr = childList_.begin(); itr != childList_.end(); itr++) {
		(*itr)->ReleaseSub();
	}
}

void GameObject::KillAllChildren()
{
	for (auto itr = childList_.begin(); itr != childList_.end();)
	{
		KillAllChildren(*itr);
		SAFE_DELETE(*itr);
		itr = childList_.erase(itr);
	}
	childList_.clear();
}

void GameObject::KillAllChildren(GameObject* object)
{
	for (auto itr = object->childList_.begin(); itr != object->childList_.end();)
	{
		KillAllChildren(*itr);
		SAFE_DELETE(*itr);
		itr = object->childList_.erase(itr);
	}
	object->childList_.clear();
	SAFE_RELEASE(object);
}

GameObject* GameObject::FindChildObject(std::string ObjectName)
{
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)
	{
		if ((*itr)->objectName_ == ObjectName)
		{
			//this��Ԃ��ƊY���I�u�W�F�N�g�̐e�̃A�h���X���Ԃ��Ă��Ă��܂�
			return *itr;
		}
		else
		{
			GameObject* obj = (*itr)->FindChildObject(ObjectName);
			if (obj != nullptr)
			{
				return obj;
			}
		}
	}
	return nullptr;
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ != nullptr)
	{
		return pParent_->GetRootJob();
	}
	else
	{
		//pParent��nullptr�Ȃ炻�ꂪRootJob�ł���
		return this;
	}
}

GameObject* GameObject::FindObject(std::string ObjectName)
{
	//RootJob(=�S�Ă̐e)�ɖ߂�A�������猟������
	return GetRootJob()->FindChildObject(ObjectName);
}

void GameObject::AddCollider(SphereCollider* Collider)
{
	Collider->SetGameObject(this);		//GameObject�ɕR�t��
	Colliderlist_.push_back(Collider);	//List�ɓ����
}

void GameObject::Collision(GameObject* pTarget)
{
	//�����Ƃ̓����蔻��͂��Ȃ�
	if (this != pTarget && pTarget->Collision_ != nullptr)
	{
		//���X�g�̃T�C�Y�������[�v
		for (auto itr = Colliderlist_.begin(); itr != Colliderlist_.end(); itr++)	//�O���ƂȂ����G���[
		{
			if (Collision_->Ishit(pTarget->Collision_))
			{
				OnCollision(pTarget);
			}
		}
	}
		//�q�I�u�W�F�N�g�̔�����Ă�
		if (!pTarget->childList_.empty())
		{
			for (auto itr = pTarget->childList_.begin(); itr != pTarget->childList_.end(); itr++)
			{	//list�̐�������A����
				Collision(*itr);
			}
		}
	
}
