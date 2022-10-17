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

//������
void SceneManager::Initialize()
{
    //�ŏ��̃V�[��������
    currentSceneID_ = SCENE_ID_SPLASH;
    nextSceneID_ = currentSceneID_;
    Instantiate<>(this);
}


void SceneManager::Update()
{
    //���̃V�[�������݂̃V�[���ƈႤ �� �V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
    if (currentSceneID_ != nextSceneID_)
    {
        //�w�i���O���[���F�ɖ߂�
        SetScreen(0, 128, 128);

        //���̃V�[���̃I�u�W�F�N�g��S�폜
        KillAllChildren();

        //���[�h�����f�[�^��S�폜
        Model::AllRelease();
        Image::AllRelease();

        //���̃V�[�����쐬
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