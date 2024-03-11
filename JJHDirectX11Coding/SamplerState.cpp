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

	// D3D11_TEXTURE_ADDRESS_BORDER : uv 1 ������ �Ʒ� BorderColor��
	// D3D11_TEXTURE_ADDRESS_MIRROR : uv 1 ������ �ſ� ��ģ��
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

	// RGBA
	// D3D11_TEXTURE_ADDRESS_BORDER�� �� uv��ǥ�� 1 �̻� �ϸ� �ؽ��� �Ѵ� �κ��� �Ʒ� ������ RGBA������ ����
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
