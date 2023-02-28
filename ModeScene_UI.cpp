#include "ModeScene_UI.h"
#include "../IntegratedEngine/Engine/Image.h"
#include "../IntegratedEngine/Engine/Input.h"
#include "../IntegratedEngine/Engine/Math.h"
#include "Engine/SceneManager.h"
#include "Storage.h"

ModeScene_UI::ModeScene_UI(GameObject* parent)
	: GameObject(parent, "ModeScene_UI")
{
	hPict_.clear();
	Func_.clear();
}

ModeScene_UI::~ModeScene_UI()
{
	hPict_.clear();
	Func_.clear();
}

void ModeScene_UI::Initialize()
{
	int pict;
	ILoad(pict, "Assets\\Button_Easy.png");
	hPict_.push_back(pict);
	Func_.insert({ pict, &ModeScene_UI::SelectEasy });

	ILoad(pict, "Assets\\Button_Hard.png");
	hPict_.push_back(pict);
	Func_.insert({ pict, &ModeScene_UI::SelectHard });

	ILoad(pict, "Assets\\Settings.png");
	hPict_.push_back(pict);
	Func_.insert({ pict, &ModeScene_UI::SelectSettings });
}

void ModeScene_UI::Update()
{
	//�}�E�X�̍��N���b�N��������
	if (Input::IsMouseDown(0))
	{
		//�ǂ̉摜�Ƀ}�E�X�J�[�\�����������Ă��邩�擾
		auto found = Func_.find(Image::IsHitCursorAny());

		//������ɂ��������Ă��Ȃ��ꍇ
		if (found == end(Func_)) {
			return;
		}

		//�������Ă���ΊY�����������s
		(this->*found->second)();
	}
}

void ModeScene_UI::Draw()
{
	for (auto i : hPict_)
	{
		Image::Draw(i);
	}
}

void ModeScene_UI::Release()
{
}

void ModeScene_UI::SelectEasy()
{
	Storage::SetDifficulty(Difficulty::EASY);
	SCENE_CHANGE(SCENE_ID_PLAY);
}

void ModeScene_UI::SelectHard()
{
	Storage::SetDifficulty(Difficulty::HARD);
	SCENE_CHANGE(SCENE_ID_PLAY);
}

void ModeScene_UI::SelectSettings()
{
	SCENE_CHANGE(SCENE_ID_SETTINGS);
}