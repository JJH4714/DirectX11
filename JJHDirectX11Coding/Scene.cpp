#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Awake()
{
	for (const auto& e : m_vecGameObject)
		if (e)
			e->Awake();
}

void Scene::Start()
{
	for (const auto& e : m_vecGameObject)
		if (e)
			e->Start();
}

void Scene::Update()
{
	for (const auto& e : m_vecGameObject)
		if (e)
			e->Update();
}

void Scene::LateUpdate()
{
	for (const auto& e : m_vecGameObject)
		if (e)
			e->LateUpdate();
}

void Scene::FixedUpdate()
{
	for (const auto& e : m_vecGameObject)
		if (e)
			e->FixedUpdate();
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_vecGameObject.push_back(gameObject);
}

void Scene::removeGameObject(std::shared_ptr<GameObject> gameObject)
{
	if (auto it = std::find(m_vecGameObject.begin(), m_vecGameObject.end(), gameObject); it != m_vecGameObject.end())
		m_vecGameObject.erase(it);
}
