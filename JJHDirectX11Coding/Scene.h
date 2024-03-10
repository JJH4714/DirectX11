#pragma once

class GameObject;

class Scene
{
	// ������ ������Ʈ���� ��� ����
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

