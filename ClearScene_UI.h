#pragma once
#include "../IntegratedEngine/Engine/MouseOperationUI.h"

class ClearScene_UI : public MouseOperationUI
{
	int hPict_;
public:
	ClearScene_UI(GameObject* parent);

	~ClearScene_UI();

	void Initialize() override;

	void ClickLeftFirst() override;

	void DrawUnique() override;

	void Release() override;
};