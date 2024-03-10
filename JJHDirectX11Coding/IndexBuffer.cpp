#include "pch.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(ComPtr <ID3D11Device> device) : m_device(device)
{
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Create(const std::vector<uint32>& indices)
{
	m_stride = sizeof(uint32);
	m_count = static_cast<uint32>(indices.size());
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.Usage = D3D11_USAGE_IMMUTABLE;	// �ﰢ�� ������ GPU���� �� ���� ������, ���� ��ĥ �ʿ� �����ϱ� �ϴ� IMMUTABLE�� ����
	// BindFlags : ���ε� �뵵
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// ���⼱ '�ε��� ����; ����� �� ���ڴ�
	// ByteWidth : ���� ũ��. ���ؽ� �ϳ� ũ�� * ���ؽ� ��ü ������
	desc.ByteWidth = static_cast<uint32>(m_stride * indices.size());

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();	// ���ؽ�(����) ������ ���� �ּ�

	// ���ؽ� ���ۿ� ������� �ް� ��
	HRESULT hr = m_device->CreateBuffer(&desc, &data, m_indexBuffer.GetAddressOf());
	CHECK_HR(hr);
}