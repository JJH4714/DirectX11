#include "pch.h"
#include "05. TextureDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"

void TextureDemo::Init()
{
	_shader = make_shared<Shader>(L"04. Texture.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();
	//GeometryHelper::CreateQuad(_geometry);
	GeometryHelper::CreateCube(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	//Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");
}

void TextureDemo::Update()
{
	_camera->Update();
}

void TextureDemo::Render()
{
	// W - V - P
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);	// ¼ÎÀÌ´õ¿¡¼­ matrix World
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);	// ¼ÎÀÌ´õ¿¡¼­ matrix View
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);	// ¼ÎÀÌ´õ¿¡¼­ matrix Projection
	_shader->GetSRV("Texture0")->SetResource(RESOURCES->Get<Texture>(L"Sannabi")->GetComPtr().Get());	//Texture2D Texture0
	
	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _indexBuffer->GetOffset());

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
