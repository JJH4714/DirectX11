#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState(ComPtr<ID3D11Device> device) : m_device(device)
{
}

SamplerState::~SamplerState()
{
}

void SamplerState::Create()
{
	// Default.hlsl - samplerState sampler0
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	// D3D11_TEXTURE_ADDRESS_BORDER : uv 1 넘으면 아래 BorderColor로
	// D3D11_TEXTURE_ADDRESS_MIRROR : uv 1 넘으면 거울 비친듯
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

	// RGBA
	// D3D11_TEXTURE_ADDRESS_BORDER일 때 uv좌표를 1 이상 하면 텍스쳐 넘는 부분은 아래 설정한 RGBA값으로 나옴
	desc.BorderColor[0] = 1.0f;
	desc.BorderColor[1] = 0.0f;
	desc.BorderColor[2] = 0.0f;
	desc.BorderColor[3] = 1.0f;

	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.0f;

	HRESULT hr = m_device->CreateSamplerState(&desc, m_samplerState.GetAddressOf());
	ASSERT(hr);
}
