//�S�ẴQ�[���I�u�W�F�N�g�̐e�ƂȂ�N���X

#pragma once

#include <list>
#include <string>
#include "CallDef.h"
#include "Transform.h"
#include "SphereCollider.h"

class GameObject
{
	GameObject* pParent_;				//�e�N���X�̃|�C���^
	const std::string	objectName_;	//�I�u�W�F�N�g�̖��O
	bool KILL;							//true�Ȃ�I�u�W�F�N�g����

protected:
	Transform	transform_;						//Transform
	std::list<GameObject*> childList_;			//�Q�[���I�u�W�F�N�g�̃��X�g�\��
	std::list<SphereCollider*> Colliderlist_;	//Collider�̃��X�g�\��
	SphereCollider* Collision_;					//Collider�̃|�C���^

public:
	GameObject();
	GameObject(GameObject* parent, const std::string& name);
	virtual ~GameObject();

	virtual void Initialize() {}	//������
	virtual void Update() {}		//�X�V
	void UpdateSub();				//�q�I�u�W�F�N�g�̍X�V
	virtual void Draw() {}			//�`��
	void DrawSub();					//�q�I�u�W�F�N�g�̕`��
	virtual void Release() {}		//���
	void ReleaseSub();

	///////////////////////////////////////////transform�Ɋւ���Z�b�^�A�Q�b�^//////////////////////////////////////////////////
	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }

	///////////////////////////////////////////�I�u�W�F�N�g�����ł�����Z�b�g///////////////////////////////////////////////////
	void KillMe() { KILL = true; }							//���ꂪ�Ă΂ꂽ��Y���I�u�W�F�N�g�͏���
	void KillAllChildren();									//�q�I�u�W�F�N�g������
	void KillAllChildren(GameObject* object);				//�����Ŏ󂯎�����I�u�W�F�N�g�̎q�I�u�W�F�N�g�����ł�����

	/////////////////////////////////////////////��������擾�������///////////////////////////////////////////////////////////
	GameObject* FindChildObject(std::string ObjectName);	//�����Ŏ󂯎�������O�Ɠ������O�̃I�u�W�F�N�g�����g�̎q���ɂ��Ȃ�����������֐�
	GameObject* GetRootJob();								//RootJob��T���֐�
	GameObject* FindObject(std::string ObjectName);			//�����Ŏ󂯎�������O�Ɠ������O�̃I�u�W�F�N�g��T���֐�
	std::string GetObjectName() { return objectName_; }		//�I�u�W�F�N�g�̖��O���擾
	GameObject* GetParent() { return pParent_; }			//�e�A�h���X���擾

	///////////////////////////////////////////////////Collision�֌W////////////////////////////////////////////////////////////
	void AddCollider(SphereCollider* Collider);				//Collider��GameObject�����т��Alist�ɒǉ�����
	void Collision(GameObject* pTarget);					//�����蔻����s��
	virtual void OnCollision(GameObject* pTarget) {}		//���������炱�ꂪ�Ă΂��(override��p)

	//�N���X�e���v���[�g
	template <class T>
	T* Instantiate(GameObject* pParent)
	{
		T* pNewObject = new T(pParent);
		if (pParent != nullptr)
		{
			pParent->childList_.push_back(pNewObject);
		}
		pNewObject->Initialize();
		return pNewObject;
	}
};