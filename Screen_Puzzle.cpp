#include "Screen_Puzzle.h"
#include "Engine/Camera.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include <algorithm>

Screen_Puzzle::Screen_Puzzle(GameObject* parent)
	: GameObject(parent, "Screen_Puzzle"), hModel_(-1)
{
	ZeroMemory(Board_, sizeof(Board_));
	Board_[BoardSize_ - 1][BoardSize_ - 1] = Empty_;
}

Screen_Puzzle::~Screen_Puzzle()
{
}

void Screen_Puzzle::Initialize()
{
}

void Screen_Puzzle::Update()
{
	if (Input::IsMouseDown(0))
	{
		//ビューポート行列
		float w = (float)Direct3D::scrWidth / 2.0f;
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

		float distance = 9999.0f;
		bool Ishit = false;

		int boardX, boardZ;

		for (int x = 0; x < BoardSize_; x++)
		{
			for (int z = 0; z < BoardSize_; z++)
			{
						RayCastData data;
						XMStoreFloat3(&data.start, front);
						XMStoreFloat3(&data.dir, ray);

						Transform Tr;
						Tr.position_ = XMFLOAT3((float)x, NULL, (float)z);
						Model::SetTransform(hModel_, Tr);

						Model::RayCast(hModel_, data);

						if (data.hit && distance > data.dist)
						{
							distance = data.dist;
							boardX = x;
							boardZ = z;
							Ishit = true;
						}
				}
		}
		if (Ishit)
		{
			Swap(boardX, boardZ);
		}
	}
}

void Screen_Puzzle::Draw()
{
}

void Screen_Puzzle::Release()
{
}

void Screen_Puzzle::Swap(int x, int z)
{
	//隣り合っている場所にEmptyが存在するか
	for (Move Dir : Direction)
	{
		int moveX, moveZ;
		moveX = x + Dir.moveLtR;
		moveZ = z + Dir.moveHLw;
		if(moveX >= NULL && moveX < BoardSize_ && moveZ >= NULL && moveZ < BoardSize_)
		//あったら移動させる
		if (Board_[moveX][moveZ] == Empty_)
		{
			std::swap(Board_[x][z], Board_[x + Dir.moveLtR][z + Dir.moveHLw]);
			return;
		}
	}
}