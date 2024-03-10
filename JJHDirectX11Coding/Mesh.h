#pragma once
#include "ResourceBase.h"
class Mesh : public ResourceBase
{
public:
	Mesh(ComPtr<ID3D11Device> device);
	virtual ~Mesh();

	void CreateDefaultRectangle();

	std::shared_ptr<VertexBuffer> GetVertexBuffer() { return m_vertexBuffer; }
	std::shared_ptr<IndexBuffer> GetIndexBuffer() { return m_indexBuffer; }

private:
	ComPtr<ID3D11Device> m_device;

	// Mesh - 물체의 형태
	std::shared_ptr<Geometry<VertexTextureData>> m_geometry;
	std::shared_ptr<VertexBuffer> m_vertexBuffer;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
};

