#pragma once

//DELETE�������Ăяo���}�N�����쐬
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
//�z���DELETE����}�N��
#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete[] p; p = nullptr;}
//RELEASE�����l�Ƀ}�N���쐬
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

//HRESULT�����s�����Ƃ���Release�Ȃ��ŌĂяo���}�N��
#define HR_FAILED(hr, text) if(FAILED(hr)){MessageBox(NULL, text, L"Error", MB_OKCANCEL);return hr; }
//HRESULT�����s�����Ƃ���Release����ŌĂяo���}�N��
#define HR_FAILED_RELEASE(hr, text, p) if(FAILED(hr)){MessageBox(NULL, text, L"Error", MB_OKCANCEL); SAFE_RELEASE(p);return hr; }

//�V�[���؂�ւ����s���}�N��
#define SCENE_CHANGE(SCENE_ID) SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager"); pSceneManager->ChangeScene(SCENE_ID);

//���͈̔͂Ɏ��߂����
#define CLAMP(i, Min, Max) i = min(max( i, Min), Max);