#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Direct3D.h"
#include "../IntegratedEngine/Engine/Input.h"
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
	float dist = MakeMouseRay();

	//�J��������O�ɂ���h�A�ɂ͓�����Ȃ��悤�ɂ���
	//�}�E�X���������^�C�~���O�őΏۂ��w���Ă��邩
	if (RayHit_ && Input::IsMouseDown(0) && dist > 1.0f)
	{
		IsMouse_[0] = true;
	}
	//�}�E�X�𗣂����^�C�~���O�őΏۂ��w���Ă��邩
	if (RayHit_ && Input::IsMouseUp(0) && dist > 1.0f)
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
	if (!Input::IsMouse(0))
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
		Model::Draw(hModel_, Chroma, UCHAR_MAX, UCHAR_MAX);
	}
	else
	{
		Model::Draw(hModel_, 2);
	}
}

float Door::MakeMouseRay()
{
	//�}�E�X�ʒu
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.x = mousePosFront.x;
	mousePosFront.z = 0;

	XMVECTOR front = SetInvMat(mousePosFront);

	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.x = mousePosBack.x;
	mousePosBack.z = 1.0f;

	XMVECTOR back = SetInvMat(mousePosBack);

	XMVECTOR ray = back - front;
	ray = XMVector3Normalize(ray);

	RayCastData data;

	XMStoreFloat3(&data.start, front);
	XMStoreFloat3(&data.dir, ray);

	Model::SetTransform(hModel_, transform_);
	Model::RayCast(hModel_, data);

	RayHit_ = data.hit;

	return data.dist;
}

XMVECTOR Door::SetInvMat(XMFLOAT3 pos)
{
	//�r���[�|�[�g�s��
	float w = 0;
	switch (Direct3D::SplitScrMode)
	{
	case SCREEN_FULL: w = (float)Direct3D::scrWidth / 2.0f; break;
	case SCREEN_SPLIT_2: w = (float)Direct3D::scrWidth / 4.0f; break;
	default: break;
	}
	float h = (float)Direct3D::scrHeight / 2.0f;
	XMMATRIX vp =
	{
		w, 0, 0, 0,
		0,-h, 0, 0,
		0, 0, 1, 0,
		w, h, 0, 1
	};

	//�e�s��̋t�s��
	XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

	XMVECTOR vPos = XMLoadFloat3(&pos);

	XMMATRIX mat = invVp * invPrj * invView;

	vPos = XMVector3TransformCoord(vPos, mat);

	return vPos;
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