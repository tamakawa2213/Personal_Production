#pragma once
#include "../IntegratedEngine/Engine/RootUI.h"
#include <map>

class ModeScene_UI : public UserInterface
{
	std::vector<int> hPict_;						//ロードした画像の配列
	std::map<int, void(ModeScene_UI::*)()> Func_;	//画像と関数の連想配列

	void SelectEasy();		//easyボタンを押下した時の処理
	void SelectHard();		//hard			〃
	void SelectSettings();	//設定			〃
public:
	ModeScene_UI(RootUI* ui);

	~ModeScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};