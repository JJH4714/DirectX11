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
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	// ��� ���� �뵵
		desc.ByteWidth = sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	// �� ������ �����ؾ� �ϴϱ�...

		// ������� ����
		HRESULT hr = m_device->CreateBuffer(&desc, nullptr, m_constantBuffer.GetAddressOf());
		CHECK_HR(hr);
	}

	void CopyData(const T& data)
	{
		// ����� ���긮�ҽ�
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		// Map - Unmap�� ¦�� �̷�
		m_deviceContext->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);

		::memcpy(
			subResource.pData,	// desc. �� ���긮�ҽ��� ���� ������
			&data,	// Ʈ������ ����
			sizeof(T));	// Ʈ������ ���� ũ��

		m_deviceContext->Unmap(m_constantBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_deviceContext;
	ComPtr<ID3D11Buffer> m_constantBuffer;
};

