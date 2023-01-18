#include "Picture.h"
#include "CallDef.h"
#include "Input.h"

namespace
{
    std::vector<PictureSet*> FileSet;      //Fbx�̍\���̂̓��I�z��
}

namespace Picture
{
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
                break;
            }
        }
        //������Ȃ������ꍇ�A�V�������[�h����
        File->pSprite = new Sprite;
        hr = File->pSprite->Initialize(filename);
        if (FAILED(hr)) //���[�h�Ɏ��s�����ꍇ
        {
            SAFE_DELETE(File->pSprite);
            SAFE_DELETE(File);
        }

        FileSet.push_back(File);
        return (int)FileSet.size() - 1;
    }

    int Load(std::string filename)
    {
        wchar_t file[CHAR_MAX];
        size_t ret;
        mbstowcs_s(&ret, file, filename.c_str(), filename.length());
        return Load(file);
    }

    void Picture::SetTransform(int hPicture, Transform transform)
    {
        FileSet[hPicture]->transform = transform;
    }

    void Picture::Draw(int hModel)
    {
        FileSet[hModel]->pSprite->Draw(FileSet[hModel]->transform);
    }

    bool IsHitCursor(int hModel)
    {
        UINT wid = FileSet[hModel]->pSprite->GetImgWidth() * FileSet[hModel]->transform.scale_.x * (75.0f / 32.0f);
        UINT hgt = FileSet[hModel]->pSprite->GetImgHeight() * FileSet[hModel]->transform.scale_.y * (75.0f / 32.0f);
        float Left = (FileSet[hModel]->transform.position_.x + 1) * (Direct3D::scrWidth / 2) - wid;
        float Right = (FileSet[hModel]->transform.position_.x + 1) * (Direct3D::scrWidth / 2) + wid;
        float Top = (-FileSet[hModel]->transform.position_.y + 1) * (Direct3D::scrHeight / 2) - hgt;
        float Bottom = (-FileSet[hModel]->transform.position_.y + 1) * (Direct3D::scrHeight / 2) + hgt;
        if (Left <= Input::GetMousePosition().x && Input::GetMousePosition().x <= Right &&
            Top <= Input::GetMousePosition().y && Input::GetMousePosition().y <= Bottom)
        {
            return true;
        }
        return false;
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