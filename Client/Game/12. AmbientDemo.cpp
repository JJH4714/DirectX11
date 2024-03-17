#include "pch.h"
#include "12. AmbientDemo.h"
#include "Engine/01. Graphics/Buffer/GeometryHelper.h"
#include "Engine/04. Component/Camera.h"
#include "Main/Camera/CameraScript.h"
#include "Engine/04. Component/MeshRenderer.h"

void AmbientDemo::Init()
{
	_shader = make_shared<Shader>(L"09. Lighting_Ambient.fx");
	
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
		if (auto meshRenderer = _obj->GetMeshRenderer())
			meshRenderer->SetShader(_shader);
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

	// object 2
	if (_obj2 = make_shared<GameObject>())
	{
		_obj2->GetOrAddTransform()->SetPosition(Vec3(0.5f, 0.f, 2.f));
		_obj2->AddComponent(make_shared<MeshRenderer>());
		if (auto meshRenderer = _obj2->GetMeshRenderer())
			meshRenderer->SetShader(_shader);
	}

	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		if (auto meshRenderer = _obj2->GetMeshRenderer())
			meshRenderer->SetMesh(mesh);
	}

	{
		auto texture = RESOURCES->Load<Texture>(L"Sannabi", L"..\\Resources\\Textures\\Sannabi.jpg");
		if (auto meshRenderer = _obj2->GetMeshRenderer())
			meshRenderer->SetTexture(texture);
	}

	{
		RENDER->Init(_shader);
	}
}

void AmbientDemo::Update()
{
	// _obj2 �� ��ġ�� �ڷ� �������� ������ ����� _obj2�� �տ� �ִ� �� ����
	// �ڵ庸��, _obj2�� �ڿ� Update�Ǳ� ������ ��ġ ������� ȭ��󿡴� �ʰ� �������� ��ü�� �տ� ��Ÿ��...
	// DSV ��������� �c
	_camera->Update();
	RENDER->Update();

	// Temp
	Vec4 LightAmbient(0.5f, 0.f, 0.f, 1.f);
	_shader->GetVector("LightAmbient")->SetFloatVector((float*)&LightAmbient);

	{
		Vec4 MaterialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&MaterialAmbient);
		_obj->Update();
	}

	{
		Vec4 MaterialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&MaterialAmbient);
		_obj2->Update();
	}
}

void AmbientDemo::Render()
{

}
