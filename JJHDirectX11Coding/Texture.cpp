#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device) : ResourceBase(ResourceType::Texture), m_device(device)
{
}

Texture::~Texture()
{
}

void Texture::Create(const std::wstring& path)
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr = ::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, &md, img);	// 이미지 가져오기
	CHECK_HR(hr);

	// 이미지를 셰이더 리소스 뷰로 만들어야 함
	hr = ::CreateShaderResourceView(m_device.Get(), img.GetImages(), img.GetImageCount(), md, m_shaderResourceView.GetAddressOf());
	CHECK_HR(hr);

	m_size.x = md.width;
	m_size.y = md.height;
}
