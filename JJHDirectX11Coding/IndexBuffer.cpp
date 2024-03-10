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

	desc.Usage = D3D11_USAGE_IMMUTABLE;	// 삼각형 정보를 GPU에게 한 번만 보내고, 딱히 고칠 필욘 없으니까 일단 IMMUTABLE로 하자
	// BindFlags : 바인딩 용도
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;	// 여기선 '인덱스 버퍼; 만드는 데 쓰겠다
	// ByteWidth : 버퍼 크기. 버텍스 하나 크기 * 버텍스 전체 사이즈
	desc.ByteWidth = static_cast<uint32>(m_stride * indices.size());

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = indices.data();	// 버텍스(정점) 정보의 시작 주소

	// 버텍스 버퍼에 결과물을 받게 됨
	HRESULT hr = m_device->CreateBuffer(&desc, &data, m_indexBuffer.GetAddressOf());
	CHECK_HR(hr);
}