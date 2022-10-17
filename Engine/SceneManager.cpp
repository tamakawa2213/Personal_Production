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

//������
void SceneManager::Initialize()
{
    //�ŏ��̃V�[��������
    currentSceneID_ = SCENE_ID_PLAY;
    nextSceneID_ = currentSceneID_;
    Instantiate<PlayScene>(this);
}


void SceneManager::Update()
{
    //���̃V�[�������݂̃V�[���ƈႤ �� �V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
    if (currentSceneID_ != nextSceneID_)
    {
        //���̃V�[���̃I�u�W�F�N�g��S�폜
        KillAllChildren();

        //���[�h�����f�[�^��S�폜
        Model::Release();
        Image::AllRelease();

        //���̃V�[�����쐬
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