#pragma once

template <typename T>
class ConstantBuffer
{
public:
	ConstantBuffer(ComPtr<ID3D11Device> device,
		ComPtr<ID3D11DeviceContext> deviceContext) : m_device(device), m_deviceContext(deviceContext)
	{}
	~ConstantBuffer() = default;

	ComPtr<ID3D11Buffer> GetComPtr() { return m_constantBuffer; }

	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC;	// CPU Write + GPU Read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// 상수 버퍼 용도
		desc.ByteWidth = sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// 매 프레임 접근해야 하니까...

		// 상수버퍼 생성
		HRESULT hr = m_device->CreateBuffer(&desc, nullptr, m_constantBuffer.GetAddressOf());
		CHECK_HR(hr);
	}

	void CopyData(const T& data)
	{
		// 연결된 서브리소스
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		// Map - Unmap이 짝을 이룸
		m_deviceContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

		::memcpy(
			subResource.pData,	// desc. 즉 서브리소스가 취할 데이터
			&data,	// 트랜스폼 정보
			sizeof(T));	// 트랜스폼 정보 크기

		m_deviceContext->Unmap(m_constantBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11Buffer> m_constantBuffer;
};

