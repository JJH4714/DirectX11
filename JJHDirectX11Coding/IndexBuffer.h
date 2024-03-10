#pragma once
class IndexBuffer
{
public:
	IndexBuffer(ComPtr<ID3D11Device> device);
	~IndexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return m_indexBuffer; }
	const uint32 GetStride() const { return m_stride; }
	const uint32 GetOffset() const { return m_offset; }
	const uint32 GetCount() const { return m_count; }

	void Create(const std::vector<uint32>& indices);

private:
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11Buffer> m_indexBuffer;

	uint32 m_stride = 0;
	uint32 m_offset = 0;
	uint32 m_count = 0;
};

