#include "Screen_Puzzle.h"
#include "Door.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Player.h"

#include <algorithm>

Screen_Puzzle::Screen_Puzzle(GameObject* parent)
	: GameObject(parent, "Screen_Puzzle"), hModel_()
{
	ZeroMemory(Board_, sizeof(Board_));
}

Screen_Puzzle::~Screen_Puzzle()
{
}

void Screen_Puzzle::Initialize()
{
	Shuffle();
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

				//Playerの位置を可視化するためのもの　後で消す
				Player* pPlayer = (Player*)GetParent();
				if (pPlayer->GetUVPos().x == x && pPlayer->GetUVPos().y == z)
				{
					const XMFLOAT3 Chroma{ 0.7f, 0.7f, 0.7f };
					Model::Draw(hModel_[Type], Chroma, 255);
				}

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

void Screen_Puzzle::Shuffle()
{
	for (int i = NULL; i < BoardSize_; i++)
	{
		for (int j = NULL; j < BoardSize_; j++)
		{
			Board_[i][j] = rand() % Board_MAX;
		}
	}
	Board_[NULL][NULL] = NULL;
	Board_[NULL][BoardSize_ - 1] = Empty_;
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
			Player* pPlayer = (Player*)GetParent();

			//押したマスがPlayerのいるマスだった場合
			if (pPlayer->GetUVPos().x == x && pPlayer->GetUVPos().y == z)
			{
				//Playerごと移動させる
				pPlayer->SetUVPos(XMFLOAT2((float)Dir.moveLtR, (float)Dir.moveHLw));
			}
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

bool Screen_Puzzle::DoorConfig(char BoardType, char DoorID)
{
	char ans = NULL;
	DoorPath data;
	bool path = false;
	switch (BoardType)
	{
	case Board_HLt: ans = data.DoorH + data.DoorLt; break;
	case Board_HR: ans = data.DoorH + data.DoorR; break;
	case Board_LwLt: ans = data.DoorLw + data.DoorLt; break;
	case Board_LwR: ans = data.DoorLw + data.DoorR; break;
	case Board_LtR: ans = data.DoorLt + data.DoorR; break;
	default: break;
	}

	switch (DoorID)
	{
	case DOOR_ID_H: path = ans & data.DoorLw; break;
	case DOOR_ID_LW: path = ans & data.DoorH; break;
	case DOOR_ID_LT: path = ans & data.DoorR; break;
	case DOOR_ID_R: path = ans & data.DoorLt; break;
	default: break;
	}
	return path;
}

char Screen_Puzzle::SendToken(XMFLOAT2 pPos, char DoorID)
{
	Board_[(int)pPos.x][(int)pPos.y];
	Direction[DoorID];
	
	int moveX, moveZ;
	moveX = (int)pPos.x + Direction[DoorID].moveLtR;
	moveZ = (int)pPos.y - Direction[DoorID].moveHLw;

	if (Board_[moveX][moveZ] != Empty_)
	{

		if (moveX >= NULL && moveX < BoardSize_ && moveZ >= NULL && moveZ < BoardSize_)
		{
			if (DoorConfig(Board_[moveX][moveZ], DoorID))
			{
				Player* pPlayer = (Player*)GetParent();
				pPlayer->SetUVPos(XMFLOAT2((float)Direction[DoorID].moveLtR, (float)-Direction[DoorID].moveHLw));
				return Board_[moveX][moveZ];
			}
		}
	}

	return Board_MAX;
}