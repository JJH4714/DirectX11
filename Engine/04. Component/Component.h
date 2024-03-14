#pragma once

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,	// ��ü�� �׷����� �� ����ϴ� ������Ʈ
	Camera,
	Animator,
	
	Script,
	End,
};

enum
{
	// ���� ������Ʈ ī��Ʈ(������ 0~3���� ����, ���ķ� �߰��� �� �־...)
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};

class Component
{
public:
	Component(ComponentType componentType);
	virtual ~Component();

	virtual void Awake() {}
	virtual void Start() {}
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void FixedUpdate() {}

	ComponentType GetType() { return m_componentType; }

	std::shared_ptr<GameObject> GetGameObject();
	std::shared_ptr<Transform> GetTransform();

	void SetGameObject(std::shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

	//@@ JJH - _SetGameObject�� �����ϰ� ���� ������ ���� ���
	// friend ���� private->public���� ����
	// ������ ���� ���� ����ٸ� �ٽ� �����ϴ� �͵� �����غ���...
	//friend class GameObject;
	//void _SetGameObject(std::shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

protected:
	ComponentType m_componentType;
	std::weak_ptr<GameObject> m_gameObject;

};