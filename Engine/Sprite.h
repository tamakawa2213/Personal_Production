#pragma once
#include "Direct3D.h"
#include "Texture.h"
#include "Transform.h"

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

class Sprite
{
	//コンスタントバッファー
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
		XMFLOAT4	color;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
protected:
	DWORD	vertexNum_;		//頂点数
	VERTEX* vertices_;		//頂点情報
	ID3D11Buffer* pVertexBuffer_;		//頂点バッファ
	HRESULT hr;

	DWORD indexNum;			//インデックス数
	int* index_;			//インデックス情報
	ID3D11Buffer* pIndexBuffer_;		//インデックスバッファ

	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;		//テクスチャ

public:
	Sprite();
	~Sprite();
	HRESULT Initialize(LPCWSTR fileName);
	void Draw(Transform& transform, XMFLOAT4 color);
	void Release();
	void RayCast(RayCastData* data);
private:
	XMMATRIX size_;	//画像のサイズ
	virtual void Index();
	HRESULT CreateVertexBuffer();		//頂点バッファを作成

	virtual void Vertex();
	HRESULT CreateIndexBuffer();		//インデックスバッファを作成

	HRESULT CreateConstantBuffer();		//コンスタントバッファ作成

	HRESULT LoadTexture(LPCWSTR fileName);				//テクスチャをロード


	//---------Draw関数から呼ばれる関数---------
	void PassDataToCB(Transform& transform, XMFLOAT4 color);	//コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();							//各バッファをパイプラインにセット
};