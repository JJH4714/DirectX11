#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Game.h"
#include "Animator.h"

SceneManager::SceneManager(std::shared_ptr<Graphics> graphics) : m_graphics(graphics)
{
}

void SceneManager::Init()
{
	if (m_activeScene)
	{
		m_activeScene->Awake();
		m_activeScene->Start();
	}
}

void SceneManager::Update()
{
	if (m_activeScene)
	{
		m_activeScene->Update();
		m_activeScene->LateUpdate();

		m_activeScene->FixedUpdate();
	}
}

void SceneManager::LoadScene(std::wstring sceneName)
{
	// Test
	m_activeScene = _LoadTestScene();
	Init();
}

std::shared_ptr<Scene> SceneManager::_LoadTestScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	
	std::shared_ptr<GameObject> monster = std::make_shared<GameObject>(
			m_graphics->GetDevice());
	if (monster)
	{
		monster->GetOrAddTransform();
		auto meshRenderer = std::make_shared<MeshRenderer>(m_graphics->GetDevice());
		monster->AddComponent(meshRenderer);

		// TODO : Material
		auto material = G_Game->GetResourceManager()->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);

		auto mesh = G_Game->GetResourceManager()->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);

		auto animator = std::make_shared<Animator>();
		auto animation = G_Game->GetResourceManager()->Get<Animation>(L"SnakeAnim");
		animator->SetAnimation(animation);
		monster->AddComponent(animator);

		scene->AddGameObject(monster);
	}

	// Camera
	std::shared_ptr<GameObject> camera = std::make_shared<GameObject>(m_graphics->GetDevice());
	if (camera)
	{
		camera->GetOrAddTransform();
		camera->AddComponent(std::make_shared<Camera>());
		scene->AddGameObject(camera);
	}

	return scene;
}
