#include "Door.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

Door::Door(GameObject* parent)
	: GameObject(parent, "Door"), hModel_(-1), RayHit_(false), DoorID_(NULL)
{
}

Door::~Door()
{
}

void Door::Initialize()
{
	hModel_ = Model::Load("Assets\\Door.fbx");
	assert(hModel_ >= NULL);
}

void Door::Update()
{
	//ビューポート行列
	float w = (float)Direct3D::scrWidth / 4.0f;
	float h = (float)Direct3D::scrHeight / 2.0f;
	XMMATRIX vp =
	{
		w, 0, 0, 0,
		0,-h, 0, 0,
		0, 0, 1, 0,
		w, h, 0, 1
	};

	//各行列の逆行列
	XMMATRIX invVp = XMMatrixInverse(nullptr, vp);
	XMMATRIX invPrj = XMMatrixInverse(nullptr, Camera::GetProjectionMatrix());
	XMMATRIX invView = XMMatrixInverse(nullptr, Camera::GetViewMatrix());

	//マウス位置
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = NULL;

	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.z = 1.0f;

	XMVECTOR front = XMLoadFloat3(&mousePosFront);
	XMVECTOR back = XMLoadFloat3(&mousePosBack);

	XMMATRIX mat = invVp * invPrj * invView;

	front = XMVector3TransformCoord(front, mat);
	back = XMVector3TransformCoord(back, mat);

	XMVECTOR ray = back - front;
	ray = XMVector3Normalize(ray);

	RayCastData data;
	XMStoreFloat3(&data.start, front);
	XMStoreFloat3(&data.dir, ray);

	Model::SetTransform(hModel_, transform_);
	Model::RayCast(hModel_, data);

	RayHit_ = data.hit;

	if (RayHit_ && Input::IsMouseDown(0) && data.dist > 1.0)
	{
		int i = 0;
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

void Door::SetID(char ID)
{
	DoorID_ = ID;
}
