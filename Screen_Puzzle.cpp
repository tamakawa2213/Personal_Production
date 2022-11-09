#include "Screen_Puzzle.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"

#include <algorithm>

Screen_Puzzle::Screen_Puzzle(GameObject* parent)
	: GameObject(parent, "Screen_Puzzle"), hModel_()
{
	ZeroMemory(Board_, sizeof(Board_));
	Board_[NULL][BoardSize_ - 1] = Empty_;
}

Screen_Puzzle::~Screen_Puzzle()
{
}

void Screen_Puzzle::Initialize()
{
	Board_[1][0] = 3;
	std::string Filename[Board_MAX] = { "Board_HLt" ,"Board_HR" , "Board_LwLt" , "Board_LwR" , "Board_LtR" };
	for (int i = NULL; i < Board_MAX; i++)
	{
		std::string Name = "Assets\\" + Filename[i] + ".fbx";
		hModel_[i] = Model::Load(Name);
		assert(hModel_ >= NULL);
	}
}

void Screen_Puzzle::Update()
{
	bool Ishit = MakeMouseRay();

	//いずれかのパネルにカーソルが当たっていて左クリックをしたら呼び出す
	if (Input::IsMouseDown(0) && Ishit)
	{
		Swap(PuzX_, PuzZ_);
	}

}

void Screen_Puzzle::Draw()
{
	for (char x = NULL; x < BoardSize_; x++)
	{
		for (char z = NULL; z < BoardSize_; z++)
		{
			int Type = Board_[x][z];
			if (Type != Empty_)
			{
				Transform Tr = transform_;
				Tr.position_ = XMFLOAT3(x, NULL, z);
				Model::SetTransform(hModel_[Type], Tr);

				if (PuzX_ == x && PuzZ_ == z)
				{
					const XMFLOAT3 Chroma{ 0.5f, 0.5f, 0.5f };
					Model::Draw(hModel_[Type], Chroma, 200);
				}
				else
				{
					Model::Draw(hModel_[Type]);
				}
			}
		}
	}
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

bool Screen_Puzzle::MakeMouseRay()
{
	//マウス位置
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.x = mousePosFront.x - (Direct3D::scrWidth / VpNum);
	mousePosFront.z = NULL;

	XMVECTOR front = SetInvMat(mousePosFront);

	XMFLOAT3 mousePosBack = Input::GetMousePosition();
	mousePosBack.x = mousePosBack.x - (Direct3D::scrWidth / VpNum);
	mousePosBack.z = 1.0f;

	XMVECTOR back = SetInvMat(mousePosBack);

	XMVECTOR ray = back - front;
	ray = XMVector3Normalize(ray);

	float distance = 9999.0f;
	bool Ishit = false;

	for (int x = 0; x < BoardSize_; x++)
	{
		for (int z = 0; z < BoardSize_; z++)
		{
			for (int type = NULL; type < Board_MAX; type++)
			{
				RayCastData data;
				XMStoreFloat3(&data.start, front);
				XMStoreFloat3(&data.dir, ray);

				Transform Tr;
				Tr.position_ = XMFLOAT3((float)x, 0, (float)z);
				Model::SetTransform(hModel_[type], Tr);

				Model::RayCast(hModel_[type], data);

				if (data.hit && distance > data.dist)
				{
					distance = data.dist;
					PuzX_ = x;
					PuzZ_ = z;
					Ishit = true;
				}
			}
		}
	}
	return Ishit;
}

XMVECTOR Screen_Puzzle::SetInvMat(XMFLOAT3 pos)
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

	XMVECTOR vPos = XMLoadFloat3(&pos);

	XMMATRIX mat = invVp * invPrj * invView;

	vPos = XMVector3TransformCoord(vPos, mat);

	return vPos;
}