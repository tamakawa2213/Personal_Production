#include "Screen_Puzzle.h"
#include "Door.h"
#include "../IntegratedEngine/Engine/Camera.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Math.h"
#include "../IntegratedEngine/Engine/Model.h"
#include "Goal.h"
#include "Judge.h"
#include "Pin.h"
#include "Player.h"
#include "Procedural.h"
#include "Storage.h"
#include <random>

namespace
{
	static const char UnderSide = 8;	//ボードの下半分
	static const char RightSide = 2;	//ボードの右半分
	static const int Empty_ = -1;			//空白のマス
	static const int TIMETOMOVE = 60;		//移動にかける時間
	static const int BOARDTOTAL_ = 16;		//盤面のマスの総数

	//各方向のドアを持っている番号のタグ付け
	const char DoorHi[2] = { (char)Board::HLt, (char)Board::HR };
	const char DoorLw[2] = { (char)Board::LwLt, (char)Board::LwR };
	const char DoorR[3] = { (char)Board::HR, (char)Board::LwR, (char)Board::LtR };
	const char DoorLt[3] = { (char)Board::HLt, (char)Board::LwLt, (char)Board::LtR };

	enum class DOOR_ID
	{
		H = 0,
		LW,
		LT,
		R
	};

	struct DoorPath	//通れるドアをビットで示す(上、下、右、左の順)
	{
		const char DoorH = 0x01 << 3;
		const char DoorLw = 0x01 << 2;
		const char DoorLt = 0x01 << 1;
		const char DoorR = 0x01 << 0;
	};

	struct Move
	{
		int moveHLw;
		int moveLtR;
	};

	const Move Direction[4]
	{
		{0,-1},		//上
		{0,1},		//下
		{1,0},		//左
		{-1,0}		//右
	};
}

Screen_Puzzle::Screen_Puzzle(GameObject* parent)
	: GameObject(parent, "Screen_Puzzle"), hModel_(), Wait_(false), Moving_(0), MoveDir_(0),
	MovingPanel_(0), pPlayer_(nullptr), Mode_(0), SeedData_(0), GoalPos_(0)
{
	ZeroMemory(Board_, sizeof(Board_));
	DecidedData_.clear();
}

Screen_Puzzle::~Screen_Puzzle()
{
	DecidedData_.clear();
}

void Screen_Puzzle::Initialize()
{
	pPlayer_ = (Player*)GetParent();
	AssignPuzzle();
	Shuffle();
	std::string Filename[(char)Board::MAX] = { "Board_HLt" ,"Board_HR" , "Board_LwLt" , "Board_LwR" , "Board_LtR" };
	for (int i = 0; i < (char)Board::MAX; i++)
	{
		std::string Name = "Assets\\" + Filename[i] + ".fbx";
		hModel_[i] = Model::Load(Name);
		assert(hModel_ >= 0);
	}
	Mode_ = (char)Storage::GetDifficulty();
	Instantiate<Pin>(this);
}

void Screen_Puzzle::Update()
{

	if (Wait_)
	{
		Moving();
	}
	else if(!pPlayer_->GetWait())
	{
		bool Ishit = MakeMouseRay();

		//いずれかのパネルにカーソルが当たっていて左クリックをしたら呼び出す
		if (Input::IsMouseDown(0) && Ishit)
		{
			Swap(PuzX_, PuzZ_);
		}

		//右クリックでピン差し
		if (Input::IsMouseDown(1) && Ishit)
		{
			PrickPin();
		}
	}
}

void Screen_Puzzle::Draw()
{
	for (char x = 0; x < BoardSize_; x++)
	{
		for (char z = 0; z < BoardSize_; z++)
		{
			int Type = Board_[x][z];
			if (Type != Empty_)
			{
				Transform Tr = transform_;
				Tr.position_ = XMFLOAT3(x, 0, z);

				Model::SetTransform(hModel_[Type], Tr);

				//Easyモードならば現在位置を表示
				if (pPlayer_->GetUVPos().x == x && pPlayer_->GetUVPos().y == z && Mode_ == 0)
				{
					const XMFLOAT3 Chroma{ 0.7f, 0.7f, 0.7f };
					Model::Draw(hModel_[Type], Chroma, UCHAR_MAX);
				}

#if _DEBUG		//デバッグモードでのみ表示
				/*Goal* pGoal = (Goal*)FindObject("Goal");
				if (pGoal->GetUVPos().x == x && pGoal->GetUVPos().y == z)
				{
					const XMFLOAT3 Chroma{ 0.7f, 0.7f, 0.7f };
					Model::Draw(hModel_[Type], Chroma, UCHAR_MAX, UCHAR_MAX);
				}
				SAFE_RELEASE(pGoal);*/
#endif
				
				if (PuzX_ == x && PuzZ_ == z)
				{
					if (!Wait_)
					{
						const XMFLOAT3 Chroma{ 0.5f, 0.5f, 0.5f };
						Model::Draw(hModel_[Type], Chroma, UCHAR_MAX);
					}
				}
				else
				{
					Model::Draw(hModel_[Type]);
				}
			}
			else
			{
				//移動しているマスの処理
				if (Moving_)
				{
					Transform Tr = transform_;
					Tr.position_ = XMFLOAT3(x, 0, z);
					float move = Moving_;
					switch (MoveDir_)
					{
					case 0x08: Tr.position_.z += (move / TIMETOMOVE); break;
					case 0x04: Tr.position_.z -= (move / TIMETOMOVE); break;
					case 0x02: Tr.position_.x -= (move / TIMETOMOVE); break;
					case 0x01: Tr.position_.x += (move / TIMETOMOVE); break;
					}
					Model::SetTransform(hModel_[MovingPanel_], Tr);
					if (pPlayer_->GetUVPos().x == PuzX_ && pPlayer_->GetUVPos().y == PuzZ_ && Mode_ == 0)
					{
						const XMFLOAT3 Chroma{ 0.7f, 0.7f, 0.7f };
						Model::Draw(hModel_[MovingPanel_], Chroma, UCHAR_MAX);
					}
					else
					{
						Model::Draw(hModel_[MovingPanel_]);
					}
				}
			}
		}
	}
}

void Screen_Puzzle::Release()
{
	//SAFE_RELEASE(pPlayer_);
}

void Screen_Puzzle::AssignPuzzle()
{
	//ゴールと空白の位置の決定
	AssignGoal();

	//ゴールに繋がる部屋を隣に生成する
	switch (DecidedData_.at(1) % 2)
	{
	case 0: //偶数の場合
		//右側にドアを持つパネルのみで判断
		Board_[(char)(DecidedData_.at(1) / BoardSize_)][(char)((DecidedData_.at(1) + 1) % BoardSize_)] = DoorLt[SeedData_ % 3];
		DecidedData_.push_back(DecidedData_.at(1) + 1);
		break;
	case 1: //奇数の場合
		//左側にドアを持つパネルのみで判断
		Board_[(char)(DecidedData_.at(1) / BoardSize_)][(char)((DecidedData_.at(1) - 1) % BoardSize_)] = DoorR[SeedData_ % 3];
		DecidedData_.push_back(DecidedData_.at(1) - 1);
		break;
	}

	char BoardDecide = 0;	//生成するパネルの番号
	//その他のパズルを作成
	while (DecidedData_.size() < BOARDTOTAL_)
	{
		auto Find = std::find(DecidedData_.begin(), DecidedData_.end(), BoardDecide);
		//決定済みデータにBoardDecideの値が存在しなければ
		if (Find == DecidedData_.end())
		{	//負の値になることを防ぐためにUINT型にキャストする
			Board_[(char)(BoardDecide / BoardSize_)][(char)(BoardDecide % BoardSize_)] = (UINT)((SeedData_ + BoardDecide) / (BoardDecide + 1)) % (char)Board::MAX;
			DecidedData_.push_back(BoardDecide);
		}
		BoardDecide++;
	}
}

void Screen_Puzzle::Shuffle()
{
	//シャッフルには疑似乱数を使用
	//意図 : random_deviceの方が精度はいいが、生成させる回数が多く、負担軽減のためにこちらを使用
	srand((unsigned int)time(NULL));

	Goal* pGoal = (Goal*)FindObject("Goal");

	//シャッフルする回数は80∼160の偶数回のみとする
	//意図 : 15パズルの仕様上、奇数回入れ替えたものは初期の配置に絶対に戻せないため
	int ShuffleTimes = (rand() % 40) * 2 + 80;
	std::vector<char> Pannel;
	Pannel.clear();
	//生成された回数だけループ
	for (int i = 0; i < ShuffleTimes; i++)
	{
		while (Pannel.size() < 2)
		{
			Pannel.push_back((UCHAR)(rand() % BOARDTOTAL_));
		}

		if (Pannel.at(0) != Pannel.at(1))
		{
			std::swap(Board_[(char)(Pannel.at(0) / BoardSize_)][(char)(Pannel.at(0) % BoardSize_)], Board_[(char)(Pannel.at(1) / BoardSize_)][(char)(Pannel.at(1) % BoardSize_)]);
			if (std::any_of(Pannel.begin(), Pannel.end(), [=](char data) {return data == GoalPos_; }))	//GoalPos_と一致する要素があれば
			{
				//GoalPos_と一致しないほうの要素を取り出す
				auto change = std::find_if_not(Pannel.begin(), Pannel.end(), [=](char data) {return data == GoalPos_; });
				GoalPos_ = *change;
			}
		}
		Pannel.clear();
	}

	//Playerの位置 = Emptyにならないようにする
	int roop = 0;
	while (roop % 2 != 0 || Board_[(char)pPlayer_->GetUVPos().x][(char)pPlayer_->GetUVPos().y] == Empty_ ||
		GoalPos_ == pPlayer_->GetUVPos().x * BoardSize_ + pPlayer_->GetUVPos().y)
	{
		while (Pannel.size() < 2)
		{
			Pannel.push_back(rand() % BOARDTOTAL_);
		}

		std::swap(Board_[(char)(Pannel.at(0) / BoardSize_)][(char)(Pannel.at(0) % BoardSize_)], Board_[(char)(Pannel.at(1) / BoardSize_)][(char)(Pannel.at(1) % BoardSize_)]);
		if (std::any_of(Pannel.begin(), Pannel.end(), [=](char data) {return data == GoalPos_; }))	//GoalPos_と一致する要素があれば
		{
			//GoalPos_と一致しないほうの要素を取り出す
			auto change = std::find_if_not(Pannel.begin(), Pannel.end(), [=](char data) {return data == GoalPos_; });
			GoalPos_ = *change;
		}
		Pannel.clear();
		roop++;
	}

	//シャッフル後の位置を送信
	pGoal->InitialPosition(GoalPos_);

	//Player側に初期位置のIDを送る
	Board_[(char)pPlayer_->GetUVPos().x][(char)pPlayer_->GetUVPos().y] = pPlayer_->GetID();
}

void Screen_Puzzle::AssignGoal()
{
	Procedural::SetSeed();
	SeedData_ = Procedural::FormValue();	//とりあえず値を受け取る

	//ゴールの初期位置の判定
	if (SeedData_ < 0)				//0未満ならば
	{
		GoalPos_ = UnderSide;		//下半分に置く
	}
	if (SeedData_ & 1)				//奇数ならば
	{
		GoalPos_ += RightSide;		//右半分に置く
	}
	if (Math::GetDigits(SeedData_, 0, 0) > Math::GetDigits(SeedData_, 1, 1))	//1桁目が2桁目より大きければ
	{
		GoalPos_ += UnderSide / 2;	//半分で区切った内の下段に置く
	}
	if (Math::GetDigits(SeedData_, 5, 5) > Math::GetDigits(SeedData_, 4, 4))	//6桁目が5桁目より大きければ
	{
		GoalPos_ += RightSide / 2;	//半分で区切った内の右側に置く
	}

	//決定した値にゴールを配置
	Goal* pGoal = (Goal*)FindObject("Goal");
	pGoal->InitialPosition(GoalPos_);
	SAFE_RELEASE(pGoal);

	//Emptyの位置を決める
	char EmpX, EmpZ;
	EmpX = ((char)(GoalPos_ / UnderSide) + 1) % 2;	//ゴールが置かれている場所が上半分ならEmptyを下にする
	EmpZ = GoalPos_ % 2;

	if (EmpX == 1)
		EmpX = 3;

	if (EmpZ == 1)
		EmpZ = 3;

	CLAMP(EmpX, 0, 3);
	CLAMP(EmpZ, 0, 3);

	Board_[EmpX][EmpZ] = Empty_;
	DecidedData_.push_back(EmpX * BoardSize_ + EmpZ);

	//ゴールがあるマスの部屋タイプのみここで決定させる
	//意図 : 到達不可のマスが生成されることを防ぐため
	//同時にEmptyマスの位置を決定
	switch (GoalPos_ % 2)
	{
	case 0: //偶数の場合
		//右側にドアを持つパネルのみで判断
		Board_[(char)(GoalPos_ / BoardSize_)][(char)(GoalPos_ % BoardSize_)] = DoorR[SeedData_ % 3];
		break;
	case 1: //奇数の場合
		//左側にドアを持つパネルのみで判断
		Board_[(char)(GoalPos_ / BoardSize_)][(char)(GoalPos_ % BoardSize_)] = DoorLt[SeedData_ % 3];
		break;
	}
	DecidedData_.push_back(GoalPos_);
}

void Screen_Puzzle::Swap(int x, int z)
{
	//隣り合っている場所にEmptyが存在するか
	for (Move Dir : Direction)
	{		
		int moveX, moveZ;
		moveX = x + Dir.moveLtR;
		moveZ = z + Dir.moveHLw;
		if(moveX >= 0 && moveX < BoardSize_ && moveZ >= 0 && moveZ < BoardSize_)
		//あったら移動させる
		if (Board_[moveX][moveZ] == Empty_)
		{
			DoorPath path;
			Wait_ = true;
			if (Dir.moveHLw != 0)
			{
				PuzZ_ += Dir.moveHLw;
				switch (Dir.moveHLw)
				{
				case 1: MoveDir_ = path.DoorH; break;
				case -1: MoveDir_ = path.DoorLw; break;
				}
			}
			if (Dir.moveLtR != 0)
			{
				PuzX_ += Dir.moveLtR;
				switch (Dir.moveLtR)
				{
				case 1: MoveDir_ = path.DoorR; break;
				case -1: MoveDir_ = path.DoorLt; break;
				}
			}
			//押したマスがPlayerのいるマスだった場合
			if (pPlayer_->GetUVPos().x == x && pPlayer_->GetUVPos().y == z)
			{
				//Playerごと移動させる
				pPlayer_->SetUVPos(XMFLOAT2((float)Dir.moveLtR, (float)Dir.moveHLw));
			}

			Pin* pPin = (Pin*)FindChildObject("Pin");
			if (pPin->UVPosition_.x == x && pPin->UVPosition_.y == z)
			{
				pPin->UVPosition_.x += Dir.moveLtR;
				pPin->UVPosition_.y += Dir.moveHLw;
			}
			SAFE_RELEASE(pPin);

			Goal* pGoal = (Goal*)FindObject("Goal");
			if (pGoal->GetUVPos().x == x && pGoal->GetUVPos().y == z)
			{
				pGoal->SetUVPos(XMFLOAT2((float)Dir.moveLtR, (float)Dir.moveHLw));
			}
			SAFE_RELEASE(pGoal);

			MovingPanel_ = Board_[x][z];
			std::swap(Board_[x][z], Board_[moveX][moveZ]);
			pPlayer_->SetWait(Wait_);	//Playerをwait状態にする
			Judge::AddNom();			//手数を1加算させる
			return;
		}
	}
}

void Screen_Puzzle::PrickPin()
{
	Pin* pPin = (Pin*)FindChildObject("Pin");
	if (pPin->UVPosition_.x == PuzX_ && pPin->UVPosition_.y == PuzZ_)	//ピンが刺してあるマスと同じ場所を押した場合
	{
		pPin->Disp_ = !pPin->Disp_;	//ピンの表示状態を反転
	}
	else	//違うマスなら
	{
		pPin->Disp_ = true;	//表示をtrueにして
		pPin->UVPosition_ = { (float)PuzX_, (float)PuzZ_ };	//押したマスにピンを打つ
	}
	SAFE_RELEASE(pPin);
}

bool Screen_Puzzle::MakeMouseRay()
{
	//マウス位置
	XMFLOAT3 mousePosFront = Input::GetMousePosition();
	mousePosFront.z = 0;

	XMVECTOR front = SetInvMat(mousePosFront);

	XMFLOAT3 mousePosBack = Input::GetMousePosition();

	switch (Direct3D::SplitScrMode)
	{
	case SCREEN_SPLIT_2:
		mousePosFront.x = mousePosFront.x - (Direct3D::scrWidth / 2);
		mousePosBack.x = mousePosBack.x - (Direct3D::scrWidth / 2);
		break;
	default: break;
	}
	
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
			for (int type = 0; type < (char)Board::MAX; type++)
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
	char ans = 0;
	DoorPath data;
	bool path = false;
	switch (BoardType)	//渡されたIDから通れるドアを出す
	{
	case (char)Board::HLt: ans = data.DoorH + data.DoorLt; break;
	case (char)Board::HR: ans = data.DoorH + data.DoorR; break;
	case (char)Board::LwLt: ans = data.DoorLw + data.DoorLt; break;
	case (char)Board::LwR: ans = data.DoorLw + data.DoorR; break;
	case (char)Board::LtR: ans = data.DoorLt + data.DoorR; break;
	default: break;
	}

	switch (DoorID)		//ビット演算で通れるかどうかを返す
	{
	case (char)DOOR_ID::H: path = ans & data.DoorLw; break;
	case (char)DOOR_ID::LW: path = ans & data.DoorH; break;
	case (char)DOOR_ID::LT: path = ans & data.DoorR; break;
	case (char)DOOR_ID::R: path = ans & data.DoorLt; break;
	default: break;
	}
	return path;
}

void Screen_Puzzle::Moving()
{
	Moving_++;

	//Moving_が設定した時間に達したら終了する
	if (Moving_ > TIMETOMOVE)
	{
		Moving_ = 0;
		Wait_ = false;
		pPlayer_->SetWait(Wait_);
	}
}

char Screen_Puzzle::SendToken(XMFLOAT2 pPos, char DoorID)
{
	Board_[(int)pPos.x][(int)pPos.y];
	Direction[DoorID];
	
	int moveX, moveZ;
	moveX = (int)pPos.x + Direction[DoorID].moveLtR;
	moveZ = (int)pPos.y - Direction[DoorID].moveHLw;

	//移動先が空白のマスかどうか
	if (Board_[moveX][moveZ] != Empty_)
	{
		//範囲外にいかないか
		if (moveX >= 0 && moveX < BoardSize_ && moveZ >= 0 && moveZ < BoardSize_)
		{
			if (DoorConfig(Board_[moveX][moveZ], DoorID))
			{
				//Playerの二次元座標を更新
				pPlayer_->SetUVPos(XMFLOAT2((float)Direction[DoorID].moveLtR, (float)-Direction[DoorID].moveHLw));

				return Board_[moveX][moveZ];
			}
		}
	}
	return (char)Board::MAX;
}