#pragma once

#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture(ComPtr<ID3D11Device> device);
	~Texture();

	ComPtr<ID3D11ShaderResourceView> GetComPtr() { return m_shaderResourceView; }

	void Create(const std::wstring& path);

	Vec2 GetSize() { return m_size; }

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;
	Vec2 m_size = Vec2::Zero;
};

