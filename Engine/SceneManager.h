#pragma once
#include "GameObject.h"

enum SCENE_ID
{
	SCENE_ID_SPLASH = 0,
	SCENE_ID_TITLE,
	SCENE_ID_OPTION,
	SCENE_ID_BUTTON,
	SCENE_ID_VOLUME,
	SCENE_ID_LOBBY,
	SCENE_ID_CUSTOM,
	SCENE_ID_MATCHING,
	SCENE_ID_PLAY,
	SCENE_ID_RESULT,
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