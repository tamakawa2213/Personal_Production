#pragma once
#include "../IntegratedEngine/Engine/UserInterface.h"
#include <memory>

class Text;

class ClearScene_UI : public UserInterface
{
	int hPict_;
	std::unique_ptr<Text> pText_;
public:
	ClearScene_UI();

	~ClearScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};