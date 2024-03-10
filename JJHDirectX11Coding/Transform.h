#pragma once
#include "Component.h"

class Transform : public Component
{
public:
	Transform();
	~Transform();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	Vec3 GetLocalScale() { return m_localScale; }
	void SetLocalScale(const Vec3& localScale) { m_localScale = localScale; UpdateTransform(); }
	Vec3 GetLocalRotation() { return m_localRotation; }
	void SetLocalRotation(const Vec3& localRotation) { m_localRotation = localRotation; UpdateTransform(); }
	Vec3 GetLocalPosition() { return m_localPosition; }
	void SetLocalPosition(const Vec3& localPosition) { m_localPosition = localPosition; UpdateTransform(); }

	// World
	Vec3 GetScale() { return m_scale; }
	void SetScale(const Vec3& worldScale);
	Vec3 GetRotation() { return m_rotation; }
	void SetRotation(const Vec3& worldRotation);
	Vec3 GetPosition() { return m_position; }
	void SetPosition(const Vec3& worldPosition);

	// �������� ��� 2
	Vec3 GetRigt() { return m_matWorld.Right(); }
	Vec3 GetUp() { return m_matWorld.Up(); }
	Vec3 GetLook() { return m_matWorld.Backward(); }

	Matrix GetWorldMatrix() { return m_matWorld; }

	// ���� ����
	bool HasParent() { return m_parent != nullptr; }
	std::shared_ptr<Transform> GetParent() { return m_parent; }
	void SetParent(std::shared_ptr<Transform> parent) { m_parent = parent; }

	const std::vector<std::shared_ptr<Transform>>& GetChildren() { return m_vecChildren; }
	void AddChild(std::shared_ptr<Transform> child) { m_vecChildren.push_back(child); }


private:
	Vec3 m_localScale = Vec3::One;
	Vec3 m_localRotation = Vec3::Zero;
	Vec3 m_localPosition = Vec3::Zero;

	// ĳ��
	Matrix m_matLocal = Matrix::Identity;	// �θ� �ִٸ�, ���� ��ǥ ����� �ƴ�
	Matrix m_matWorld = Matrix::Identity;	// ���� ��ȯ ���

	Vec3 m_scale;
	Vec3 m_rotation;
	Vec3 m_position;

	// �� Ʈ�������� ���� ��ü�� ��������
	Vec3 m_right;
	Vec3 m_up;
	Vec3 m_look;

	std::shared_ptr<Transform> m_parent;
	std::vector<shared_ptr<Transform>> m_vecChildren;
};

