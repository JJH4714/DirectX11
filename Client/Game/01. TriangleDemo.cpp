#include "pch.h"
#include "01. TriangleDemo.h"

void TriangleDemo::Init()
{
	_shader = make_shared<Shader>(L"01. Triangle.fx");

	_vertices.resize(3);

	_vertices[0].position = Vec3(-0.5f, 0.f, 0.f);
	_vertices[1].position = Vec3(0.f, 0.5f, 0.f);
	_vertices[2].position = Vec3(0.5f, 0.f, 0.f);

	_buffer = make_shared<VertexBuffer>();
	_buffer->Create(_vertices);
}

void TriangleDemo::Update()
{

}

void TriangleDemo::Render()
{
	uint32 stride = _buffer->GetStride();
	uint32 offset = _buffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _buffer->GetComPtr().GetAddressOf(), &stride, &offset);

	// 테크닉과 패스 번호 지정 시, 해당 테크닉 - 패스의 셰이더 작업을 수행해줌
	// ex. 0,1 인자라면 T0 P1 에서 SetVertexShader/SetPixelShader의 인자로 넘어간 각 셰이더 작업 수행
	_shader->Draw(0, 1, 3);
}
