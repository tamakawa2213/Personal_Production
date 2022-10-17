#pragma once
#include "GameObject.h"

enum SCENE_ID
{
	SCENE_ID_PLAY,
};

class SceneManager : public GameObject
{
	unsigned short currentSceneID_;		//現在のシーン
	unsigned short nextSceneID_;		//次のシーン
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);
	~SceneManager();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);


};