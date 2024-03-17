#include "pch.h"
#include "08. NormalDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"

void NormalDemo::Init()
{
	_shader = make_shared<Shader>(L"07. Normal.fx");

	// Texture
	_texture = RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");

	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	//GeometryHelper::CreateCube(_geometry);
	GeometryHelper::CreateSphere(_geometry);

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	//Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	Vec3 pos = _camera->GetTransform()->GetPosition();
	_camera->GetTransform()->SetPosition(Vec3(0.f, 0.5f, 0.f));
	_camera->GetTransform()->SetRotation(Vec3(25.f, 0.f, 0.f));
}

void NormalDemo::Update()
{
	_camera->Update();
}

void NormalDemo::Render()
{
	// W - V - P
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);	// ¼ÎÀÌ´õ¿¡¼­ matrix World
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);	// ¼ÎÀÌ´õ¿¡¼­ matrix View
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);	// ¼ÎÀÌ´õ¿¡¼­ matrix Projection
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());	//Texture2D Texture0
	_shader->GetVector("LightDir")->SetFloatVector((float*)&_lightDir);

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _indexBuffer->GetOffset());

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
