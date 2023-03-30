#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"

class PlayScene_UI : public MouseOperationUI
{
	int hPict_;
public:
	PlayScene_UI(GameObject* parent);

	~PlayScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void DrawUnique() override;

	void Release() override;
};