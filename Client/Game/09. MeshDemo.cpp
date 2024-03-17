#include "pch.h"
#include "09. MeshDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"
#include "Engine/04. Component/MeshRenderer.h"

void MeshDemo::Init()
{
	//Camera
	if (_camera = make_shared<GameObject>())
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraScript>());
	}

	if (_obj = make_shared<GameObject>())
	{
		_obj->GetOrAddTransform();
		_obj->AddComponent(make_shared<MeshRenderer>());
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetShader(make_shared<Shader>(L"07. Normal.fx"));
	}

	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetMesh(mesh);
	}

	{
		auto texture = RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetTexture(texture);
	}
}

void MeshDemo::Update()
{
	_camera->Update();
	_obj->Update();
}

void MeshDemo::Render()
{

}
