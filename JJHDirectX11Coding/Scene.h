#pragma once

class GameObject;

class Scene
{
	// 씬에서 오브젝트들을 들고 있음
public:
	Scene();
	~Scene();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void removeGameObject(std::shared_ptr<GameObject> gameObject);

	const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() { return m_vecGameObject; }

private:
	std::vector<std::shared_ptr<GameObject>> m_vecGameObject;
};

