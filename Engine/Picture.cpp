#include "Picture.h"
#include "CallDef.h"

namespace Picture
{
    std::vector<PictureSet*> FileSet;      //Fbx�̍\���̂̓��I�z��

    int Picture::Load(LPCWSTR filename)
    {
        HRESULT hr;
        PictureSet* File = new PictureSet;
        File->FileName = filename;
        for (auto itr = FileSet.begin(); itr != FileSet.end(); itr++)
        {
            //�������O�̃t�@�C�������łɃ��[�h���Ă����ꍇ
            if (File->FileName == (*itr)->FileName)
            {
                File->pSprite = (*itr)->pSprite;
                File->FindFbx = true;
                break;
            }
        }
        //������Ȃ������ꍇ�A�V�������[�h����
        if (!File->FindFbx)
        {
            File->pSprite = new Sprite;
            hr = File->pSprite->Initialize(filename);
            if (FAILED(hr)) //���[�h�Ɏ��s�����ꍇ
            {
                SAFE_DELETE(File->pSprite);
                SAFE_DELETE(File);
            }
        }

        FileSet.push_back(File);
        return (int)FileSet.size() - 1;
    }

    void Picture::SetTransform(int hPicture, Transform transform)
    {
        FileSet[hPicture]->transform = transform;
    }

    void Picture::Draw(int hModel)
    {
        FileSet[hModel]->pSprite->Draw(FileSet[hModel]->transform);
    }

    void Release()
    {
        for (int i = 0; i < FileSet.size(); i++)
        {
            if (!FileSet[i]->FindFbx)
            {
                SAFE_DELETE(FileSet[i]->pSprite);
            }
            SAFE_DELETE(FileSet[i]);
        }
        FileSet.clear();
    }
}