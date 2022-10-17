#include "SceneManager.h"
#include "Image.h"
#include "Model.h"
#include "../PlayScene.h"

SceneManager::SceneManager(GameObject* parent)
    : GameObject(parent, "SceneManager"), currentSceneID_(), nextSceneID_()
{
}

SceneManager::~SceneManager()
{
}

//初期化
void SceneManager::Initialize()
{
    //最初のシーンを準備
    currentSceneID_ = SCENE_ID_PLAY;
    nextSceneID_ = currentSceneID_;
    Instantiate<PlayScene>(this);
}


void SceneManager::Update()
{
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //そのシーンのオブジェクトを全削除
        KillAllChildren();

        //ロードしたデータを全削除
        Model::Release();
        Image::AllRelease();

        //次のシーンを作成
        switch (nextSceneID_)
        {
        case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
        }

        currentSceneID_ = nextSceneID_;
    }
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID next)
{
    nextSceneID_ = next;
}