#pragma once
#include "../IntegratedEngine/Engine/UserInterface.h"
#include <memory>
#include <vector>

class Text;

class SettingsScene_UI : public UserInterface
{
	std::unique_ptr<Text> pText_;

	std::vector<int> hPict_;							//ロードした画像の配列
public:
	SettingsScene_UI();
	~SettingsScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};