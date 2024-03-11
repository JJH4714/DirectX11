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

		// Usage : �뵵
		// D3D11_USAGE_DEFAULT : GPU �� �а� �� �� �ְ�
		// D3D11_USAGE_IMMUTABLE : GPU�� ���� ���� �ְ�
		// D3D11_USAGE_DYNAMIC : GPU�� �б�, CPU�� ���⸸ �����ϰ�
		// D3D11_USAGE_STAGING : GPU���� CPU�� ������ ����..
		// ���ؽ� ������ ���� �� ��, ��ġ ���� �� �ٲ�ٸ� ������ۿ� �߰� ������ �Ѱ��־�
		// ���ؽ� ���̴����� ó���ؾ� ��. �Ź� ���ؽ� ���۸� �ٲٴ� �� ����
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		// BindFlags : ���ε� �뵵
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// ���ؽ� ���� ����� �� ���ڴ�
		// ByteWidth : ���� ũ��. ���ؽ� �ϳ� ũ�� * ���ؽ� ��ü ������
		//desc.ByteWidth = static_cast<uint32>(sizeof(Vertex) * verticies.size());
		desc.ByteWidth = static_cast<uint32>(sizeof(T) * verticies.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = verticies.data();	// ���ؽ�(����) ������ ���� �ּ�

		// ���ؽ� ���ۿ� ������� �ް� ��
		HRESULT hr = m_device->CreateBuffer(&desc, &data, m_vertexBuffer.GetAddressOf());
		ASSERT(hr);
	}
	
private:
	ComPtr<ID3D11Device> m_device;
	// CPU �����͸� GPU�� �Ѱ���
	ComPtr<ID3D11Buffer> m_vertexBuffer;	// ���ؽ� ���� (���� ����)

	uint32 m_stride = 0;
	uint32 m_offset = 0;
	uint32 m_count = 0;
};

