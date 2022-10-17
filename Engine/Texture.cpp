#include <wincodec.h>
#include "Direct3D.h"
#include "Texture.h"

#pragma comment( lib, "WindowsCodecs.lib" )
Texture::Texture() :
	pSampler_(nullptr),
	pSRV_(nullptr),
	size_(XMMatrixIdentity())
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(LPCWSTR fileName)
{
	IWICImagingFactory* pFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pFormatConverter = nullptr;
	HRESULT hr;
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&pFactory));
	assert(hr == S_OK);
	hr = pFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"デコーダーに失敗しました", L"エラー", MB_OK);
		return hr;
	}
	pDecoder->GetFrame(0, &pFrame);
	pFactory->CreateFormatConverter(&pFormatConverter);
	pFormatConverter->Initialize(pFrame, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);

	UINT imgWidth;
	UINT imgHeight;
	pFormatConverter->GetSize(&imgWidth, &imgHeight);
	size_ = XMMatrixScaling((float)imgWidth, (float)imgHeight, 0);

	ID3D11Texture2D* pTexture;
	D3D11_TEXTURE2D_DESC texdec;
	texdec.Width = imgWidth;
	texdec.Height = imgHeight;
	texdec.MipLevels = 1;
	texdec.ArraySize = 1;
	texdec.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texdec.SampleDesc.Count = 1;
	texdec.SampleDesc.Quality = 0;
	texdec.Usage = D3D11_USAGE_DYNAMIC;
	texdec.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	texdec.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	texdec.MiscFlags = 0;
	hr = Direct3D::pDevice->CreateTexture2D(&texdec, nullptr, &pTexture);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedres;
	Direct3D::pContext->Map(pTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &hMappedres);
	pFormatConverter->CopyPixels(nullptr, imgWidth * 4, imgWidth * imgHeight * 4, (BYTE*)hMappedres.pData);
	Direct3D::pContext->Unmap(pTexture, 0);

	//サンプラー作成
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	hr = Direct3D::pDevice->CreateSamplerState(&SamDesc, &pSampler_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"サンプラー作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = Direct3D::pDevice->CreateShaderResourceView(pTexture, &srv, &pSRV_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"シェーダーの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}
	pTexture->Release();

	return S_OK;
}

void Texture::Release()
{
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}
