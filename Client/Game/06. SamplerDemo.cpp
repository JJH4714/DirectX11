#include "pch.h"
#include "06. SamplerDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"

void SamplerDemo::Init()
{
	_shader = make_shared<Shader>(L"05. Sampler.fx");

	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, 64, 64);

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
	_camera->GetTransform()->SetPosition(Vec3(pos.x, pos.y + 3, pos.z));

	RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");
}

void SamplerDemo::Update()
{
	_camera->Update();
}

void SamplerDemo::Render()
{
	// W - V - P
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);	// 셰이더에서 matrix World
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);	// 셰이더에서 matrix View
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);	// 셰이더에서 matrix Projection
	_shader->GetSRV("Texture0")->SetResource(RESOURCES->Get<Texture>(L"Sannabi")->GetComPtr().Get());	//Texture2D Texture0

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();
	enum ADDRESS_VALUE
	{
		ADDRESS_WRAP = 0,
		ADDRESS_MIRROR = 1,
		ADDRESS_CLAMP = 2,
		ADDRESS_BORDER = 3,
	};

	//_shader->GetScalar("Address")->SetInt(ADDRESS_WRAP);	// 벗어나는 범위 다 똑같이
	//_shader->GetScalar("Address")->SetInt(ADDRESS_MIRROR);	// 벗어나는 범위 거울처럼 반사
	//_shader->GetScalar("Address")->SetInt(ADDRESS_CLAMP);	// 기본값
	_shader->GetScalar("Address")->SetInt(ADDRESS_BORDER);	// 벗어나는 범위 지정한 색으로 세팅

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, _indexBuffer->GetOffset());

	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
