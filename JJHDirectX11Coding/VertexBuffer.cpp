#include "pch.h"
#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(ComPtr <ID3D11Device> device) : m_device(device)
{
}

VertexBuffer::~VertexBuffer()
{
}
