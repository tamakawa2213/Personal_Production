#pragma once
#include "../IntegratedEngine/Engine/GameObject.h"

class Text;

class SettingsScene_UI : public GameObject
{
	Text* pText_;

	std::vector<int> hPict_;							//ƒ[ƒh‚µ‚½‰æ‘œ‚Ì”z—ñ
public:
	SettingsScene_UI(GameObject* parent);
	~SettingsScene_UI();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};