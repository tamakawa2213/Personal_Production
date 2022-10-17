#include "Model.h"
#include "CallDef.h"

namespace Model
{
    std::vector<Fileset*> FileSet;      //Fbxの構造体の動的配列

    int Model::Load(std::string filename)
    {
        HRESULT hr;
        Fileset* File = new Fileset;
        File->FileName = filename;
        for (auto itr = FileSet.begin(); itr != FileSet.end(); itr++)
        {
            //同じ名前のファイルをすでにロードしていた場合
            if (File->FileName == (*itr)->FileName)
            {
                File->pFbx = (*itr)->pFbx;
                File->FindFbx = true;
                break;
            }
        }
        //見つからなかった場合、新しくロードする
        if (!File->FindFbx)
        {
            File->pFbx = new Fbx;
            hr = File->pFbx->Load(filename);
            if (FAILED(hr)) //ロードに失敗した場合
            {
                SAFE_DELETE(File->pFbx);
                SAFE_DELETE(File);
            }
        }

        FileSet.push_back(File);
        return (int)FileSet.size() - 1;
    }

    void Model::SetTransform(int hModel, Transform transform)
    {
        FileSet[hModel]->transform = transform;
    }

    void Model::Draw(int hModel)
    {
        FileSet[hModel]->pFbx->Draw(FileSet[hModel]->transform);
    }

    void Release()
    {
        for (int i = 0; i < FileSet.size(); i++)
        {
            if (!FileSet[i]->FindFbx)
            {
                SAFE_DELETE(FileSet[i]->pFbx);
            }
            SAFE_DELETE(FileSet[i]);
        }
        FileSet.clear();
    }

    void RayCast(int hModel, RayCastData& Raydata)
    {
        XMMATRIX matInv = XMMatrixInverse(nullptr, FileSet[hModel]->transform.GetWorldMatrix());

        XMFLOAT3 point = XMFLOAT3(Raydata.start.x + Raydata.dir.x, Raydata.start.y + Raydata.dir.y, Raydata.start.z + Raydata.dir.z);

        XMVECTOR start = XMLoadFloat3(&Raydata.start);
        start = XMVector3TransformCoord(start, matInv);
        XMStoreFloat3(&Raydata.start, start);

        XMVECTOR pass = XMLoadFloat3(&point);
        pass = XMVector3TransformCoord(pass, matInv);
        XMStoreFloat3(&Raydata.dir, pass - start);

        RayCastData data;

        FileSet[hModel]->pFbx->RayCast(Raydata);
    }


    void Model::PushOut(int handle, XMFLOAT3* position, float size, XMFLOAT3 dir)
    {
        XMFLOAT3 target = XMFLOAT3(position->x + dir.x, position->y + dir.y, position->z + dir.z);
        XMMATRIX matInv = XMMatrixInverse(nullptr, FileSet[handle]->transform.GetWorldMatrix());
        XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(position), matInv);
        XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
        XMVECTOR vecDir = vecTarget - vecStart;

        XMStoreFloat3(position, vecStart);
        XMStoreFloat3(&dir, vecDir);

        FileSet[handle]->pFbx->PushOut(position, size, dir);
    }
}