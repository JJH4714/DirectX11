#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return m_vertexBuffer; }
	uint32 GetStride() { return m_stride; }
	uint32 GetOffset() { return m_offset; }
	uint32 GetCount() { return m_count; }

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		m_stride = sizeof(T);
		m_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(m_stride * m_count);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, m_vertexBuffer.GetAddressOf());
		CHECK(hr);
	}

private:
	ComPtr<ID3D11Buffer> m_vertexBuffer;

	uint32 m_stride = 0;
	uint32 m_offset = 0;
	uint32 m_count = 0;
};
