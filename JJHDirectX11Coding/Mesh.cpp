#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ComPtr<ID3D11Device> device) : ResourceBase(ResourceType::Mesh), m_device(device)
{

}

Mesh::~Mesh()
{

}

void Mesh::CreateDefaultRectangle()
{
	m_geometry = std::make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(m_geometry);

	m_vertexBuffer = std::make_shared<VertexBuffer>(m_device);
	m_vertexBuffer->Create(m_geometry->GetVertices());

	m_indexBuffer = std::make_shared<IndexBuffer>(m_device);
	m_indexBuffer->Create(m_geometry->GetIndices());
}
