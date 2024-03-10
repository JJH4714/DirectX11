#pragma once

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,	// 물체가 그려지는 걸 담당하는 컴포넌트
	Camera,
	Animator,
	
	Script,
	End,
};

enum
{
	// 고정 컴포넌트 카운트(위에서 0~3번은 고정, 이후론 추가될 수 있어서...)
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

private:
	friend class GameObject;
	void _SetGameObject(std::shared_ptr<GameObject> gameObject) { m_gameObject = gameObject; }

protected:
	ComponentType m_componentType;
	std::weak_ptr<GameObject> m_gameObject;

};