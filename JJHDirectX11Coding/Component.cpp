#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(ComponentType componentType) : m_componentType(componentType)
{
}

Component::~Component()
{
}

std::shared_ptr<GameObject> Component::GetGameObject()
{
	return m_gameObject.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return m_gameObject.lock()->GetTransform();
}
