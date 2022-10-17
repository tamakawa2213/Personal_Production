#include "SceneManager.h"
#include "Image.h"
#include "Model.h"

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
    currentSceneID_ = SCENE_ID_SPLASH;
    nextSceneID_ = currentSceneID_;
    Instantiate<>(this);
}


void SceneManager::Update()
{
    //次のシーンが現在のシーンと違う ＝ シーンを切り替えなければならない
    if (currentSceneID_ != nextSceneID_)
    {
        //背景をグリーン色に戻す
        SetScreen(0, 128, 128);

        //そのシーンのオブジェクトを全削除
        KillAllChildren();

        //ロードしたデータを全削除
        Model::AllRelease();
        Image::AllRelease();

        //次のシーンを作成
        switch (nextSceneID_)
        {
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