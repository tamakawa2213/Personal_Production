#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Player.h"

Door::Door(GameObject* parent)
	: IDObject(parent, "Door"), hModel_(-1), RayHit_(false), IsMouse_()
{
}

Door::~Door()
{
}

void Door::Initialize()
{
	hModel_ = Model::Load("Assets\\Door.fbx");
	assert(hModel_ >= 0);
}

void Door::Update()
{
	RayCastData data;
	data.CreateMouseRay();
	Model::SetTransform(hModel_, transform_);
	Model::RayCast(hModel_, data);

	RayHit_ = data.hit;

	//�J��������O�ɂ���h�A�ɂ͓�����Ȃ��悤�ɂ���
	//�}�E�X���������^�C�~���O�őΏۂ��w���Ă��邩
	if (RayHit_ && Input::Mouse::Down(0) && data.dist > 1.0f)
	{
		IsMouse_[0] = true;
	}
	//�}�E�X�𗣂����^�C�~���O�őΏۂ��w���Ă��邩
	if (RayHit_ && Input::Mouse::Up(0) && data.dist > 1.0f)
	{
		IsMouse_[1] = true;
	}

	//����true�Ȃ�ΌĂяo��
	if (IsMouse_[0] && IsMouse_[1])
	{
		//�h�A���N���b�N������Player��ID�𑗂�
		SendtoPlayer();
		IsMouse_[0] = false;
		IsMouse_[1] = false;
	}

	//�����Ă��Ȃ����false�ɂȂ�
	if (!Input::Mouse::IsPush(0))
	{
		IsMouse_[0] = false;
		IsMouse_[1] = false;
	}
}

void Door::Draw()
{
	Model::SetTransform(hModel_, transform_);

	if (RayHit_)
	{
		const XMFLOAT3 Chroma{ 1.0f, 1.0f, 1.0f };
		Model::Draw(hModel_, Chroma, UCHAR_MAX);
	}
	else
	{
		Model::Draw(hModel_);
	}
}

void Door::SendtoPlayer()
{
	Player* pPlayer;
	pPlayer = (Player*)GetParent()->GetParent();	//�e�I�u�W�F�N�g�̐e�I�u�W�F�N�g��Player
	if (!pPlayer->GetWait())						//�ҋ@��Ԃ��ǂ���
	{
		pPlayer->SetID(this->GetID());				//�������g��ID�𑗂�
		pPlayer->ReceiveFromDoor();
	}
}