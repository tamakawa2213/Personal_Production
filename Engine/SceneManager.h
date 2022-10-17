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
	unsigned short currentSceneID_;		//���݂̃V�[��
	unsigned short nextSceneID_;		//���̃V�[��
public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g�i��{�I�ɃQ�[���}�l�[�W���[�j
	SceneManager(GameObject* parent);
	~SceneManager();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);


};