#pragma once
#include "04. Component/Component.h"
class Monobehaviour;
class Transform;
class Camera;
//class MeshRenderer;
//class Animator;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	std::shared_ptr<Component> GetFixedComponent(ComponentType type);
	std::shared_ptr<Transform> GetTransform();
	std::shared_ptr<Camera> GetCamera();
	//std::shared_ptr<MeshRenderer> GetMeshRenderer();
	//std::shared_ptr<Animator> GetAnimator();

	// 트랜스폼 가져오되, 없으면 만들어서라도 뱉어줌
	std::shared_ptr<Transform> GetOrAddTransform();
	void AddComponent(std::shared_ptr<Component> component);

private:
	ComPtr<ID3D11Device> m_device;

protected:
	// 오브젝트마다 하나씩만 있을 애들은 고정 사이즈로...
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_components;
	// 스크립트는 얼마든 붙일 수 있으니...
	std::vector<std::shared_ptr<Monobehaviour>> m_scripts;
};