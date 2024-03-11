#pragma once
class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return m_vertexBuffer; }
	const uint32 GetStride() const { return m_stride; }
	const uint32 GetOffset() const { return m_offset; }
	const uint32 GetCount() const { return m_count; }

	template <typename T>
	void Create(const std::vector<T>& verticies)
	{
		m_stride = sizeof(T);
		m_count = static_cast<uint32>(verticies.size());


		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		// Usage : 용도
		// D3D11_USAGE_DEFAULT : GPU 가 읽고 쓸 수 있게
		// D3D11_USAGE_IMMUTABLE : GPU만 읽을 수만 있게
		// D3D11_USAGE_DYNAMIC : GPU는 읽기, CPU는 쓰기만 가능하게
		// D3D11_USAGE_STAGING : GPU에서 CPU로 데이터 전송..
		// 버텍스 정보는 수정 안 함, 위치 같은 게 바뀐다면 상수버퍼에 추가 정보를 넘겨주어
		// 버텍스 셰이더에서 처리해야 함. 매번 버텍스 버퍼를 바꾸는 건 무리
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		// BindFlags : 바인딩 용도
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// 버텍스 버퍼 만드는 데 쓰겠다
		// ByteWidth : 버퍼 크기. 버텍스 하나 크기 * 버텍스 전체 사이즈
		//desc.ByteWidth = static_cast<uint32>(sizeof(Vertex) * verticies.size());
		desc.ByteWidth = static_cast<uint32>(sizeof(T) * verticies.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = verticies.data();	// 버텍스(정점) 정보의 시작 주소

		// 버텍스 버퍼에 결과물을 받게 됨
		HRESULT hr = m_device->CreateBuffer(&desc, &data, m_vertexBuffer.GetAddressOf());
		ASSERT(hr);
	}
	
private:
	ComPtr<ID3D11Device> m_device;
	// CPU 데이터를 GPU에 넘겨줌
	ComPtr<ID3D11Buffer> m_vertexBuffer;	// 버텍스 버퍼 (정점 버퍼)

	uint32 m_stride = 0;
	uint32 m_offset = 0;
	uint32 m_count = 0;
};

