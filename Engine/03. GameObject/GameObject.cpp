#include "pch.h"
#include "GameObject.h"
#include "04. Component/Monobehaviour.h"
#include "04. Component/Camera.h"
#include "04. Component/Transform.h"
#include "04. Component/MeshRenderer.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (const auto& e : _components)
		if(e)
			e->Awake();

	for (const auto& e : _scripts)
		if (e)
			e->Awake();
}

void GameObject::Start()
{
	for (const auto& e : _components)
		if (e)
			e->Start();

	for (const auto& e : _scripts)
		if (e)
			e->Start();
}

void GameObject::Update()
{
	for (const auto& e : _components)
		if (e)
			e->Update();

	for (const auto& e : _scripts)
		if (e)
			e->Update();

	// 임시코드
	if (GetCamera())
		return;
}

void GameObject::LateUpdate()
{
	for (const auto& e : _components)
		if (e)
			e->LateUpdate();

	for (const auto& e : _scripts)
		if (e)
			e->LateUpdate();
}

void GameObject::FixedUpdate()
{
	for (const auto& e : _components)
		if (e)
			e->FixedUpdate();

	for (const auto& e : _scripts)
		if (e)
			e->FixedUpdate();
}

std::shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return std::static_pointer_cast<Transform>(component);
}

std::shared_ptr<Camera> GameObject::GetCamera()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);
	return std::static_pointer_cast<Camera>(component);
}

std::shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::MeshRenderer);
	return std::static_pointer_cast<MeshRenderer>(component);
}

//std::shared_ptr<Animator> GameObject::GetAnimator()
//{
//	std::shared_ptr<Component> component = GetFixedComponent(ComponentType::Animator);
//	return std::static_pointer_cast<Animator>(component);
//}

std::shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
		AddComponent(std::make_shared<Transform>());

	return GetTransform(); 
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	// 그냥 this로 넘겨주게 되면 레퍼런스 카운트를 이중으로 관리하게 되어 메모리 오염...
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (FIXED_COMPONENT_COUNT > index)
		_components[index] = component;
	else
		_scripts.push_back(dynamic_pointer_cast<Monobehaviour>(component));
}
