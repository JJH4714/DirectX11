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

	// Ʈ������ ��������, ������ ������ �����
	std::shared_ptr<Transform> GetOrAddTransform();
	void AddComponent(std::shared_ptr<Component> component);

private:
	ComPtr<ID3D11Device> m_device;

protected:
	// ������Ʈ���� �ϳ����� ���� �ֵ��� ���� �������...
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> m_components;
	// ��ũ��Ʈ�� �󸶵� ���� �� ������...
	std::vector<std::shared_ptr<Monobehaviour>> m_scripts;
};