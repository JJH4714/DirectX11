#include "pch.h"
#include "17. MaterialDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"
#include "Engine/04. Component/MeshRenderer.h"

void MaterialDemo::Init()
{
	_shader = make_shared<Shader>(L"13. Lighting.fx");
	
	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto texture = RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");
			material->SetDiffuseMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		
		RESOURCES->Add(L"Sannabi", material);
	}

	//Camera
	if (_camera = make_shared<GameObject>())
	{
		_camera->GetOrAddTransform()->SetPosition(Vec3(0.f, 0.f, -10.f));
		_camera->AddComponent(make_shared<Camera>());
		_camera->AddComponent(make_shared<CameraScript>());
	}

	// object 1
	if (_obj = make_shared<GameObject>())
	{
		_obj->GetOrAddTransform();
		_obj->AddComponent(make_shared<MeshRenderer>());
	}

	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetMesh(mesh);
	}

	{
		auto material = RESOURCES->Get<Material>(L"Sannabi");
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetMaterial(material);
	}

	// object 2
	if (_obj2 = make_shared<GameObject>())
	{
		_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
		_obj2->AddComponent(make_shared<MeshRenderer>());

	}

	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"Sannabi")->Clone();
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(0.5f);

		_obj2->GetMeshRenderer()->SetMaterial(material);
	}


	{
		RENDER->Init(_shader);
	}
}
 
void MaterialDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	LightDesc lightDesc;
	lightDesc.ambient = Vec4(0.5f);
	lightDesc.diffuse = Vec4(1.f);
	lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
	lightDesc.direction = Vec3(0.f, -1.f, 0.f);
	RENDER->PushLightData(lightDesc);

	MaterialDesc materialDesc;
	materialDesc.ambient = Vec4(0.2f);
	materialDesc.diffuse = Vec4(1.f);
	materialDesc.specular = Vec4(1.f);
	RENDER->PushMaterialData(materialDesc);

	_obj->Update();
	_obj2->Update();
}

void MaterialDemo::Render()
{

}
