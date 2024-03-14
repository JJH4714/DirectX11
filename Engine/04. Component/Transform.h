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
	Vec3 GetLocalScale() { return _localScale; }
	void SetLocalScale(const Vec3& localScale) { _localScale = localScale; UpdateTransform(); }
	Vec3 GetLocalRotation() { return _localRotation; }
	void SetLocalRotation(const Vec3& localRotation) { _localRotation = localRotation; UpdateTransform(); }
	Vec3 GetLocalPosition() { return _localPosition; }
	void SetLocalPosition(const Vec3& localPosition) { _localPosition = localPosition; UpdateTransform(); }

	// World
	Vec3 GetScale() { return _scale; }
	void SetScale(const Vec3& worldScale);
	Vec3 GetRotation() { return _rotation; }
	void SetRotation(const Vec3& worldRotation);
	Vec3 GetPosition() { return _position; }
	void SetPosition(const Vec3& worldPosition);

	// �������� ��� 2
	Vec3 GetRigt() { return _matWorld.Right(); }
	Vec3 GetUp() { return _matWorld.Up(); }
	Vec3 GetLook() { return _matWorld.Backward(); }

	Matrix GetWorldMatrix() { return _matWorld; }

	// ���� ����
	bool HasParent() { return m_parent != nullptr; }
	std::shared_ptr<Transform> GetParent() { return m_parent; }
	void SetParent(std::shared_ptr<Transform> parent) { m_parent = parent; }

	const std::vector<std::shared_ptr<Transform>>& GetChildren() { return m_vecChildren; }
	void AddChild(std::shared_ptr<Transform> child) { m_vecChildren.push_back(child); }


private:
	// �θ���ǥ�踦 �������� �� Ʈ������������
	Vec3 _localScale = Vec3::One;
	Vec3 _localRotation = Vec3::Zero;
	Vec3 _localPosition = Vec3::Zero;

	// ĳ��
	Matrix _matLocal = Matrix::Identity;	// �θ� �ִٸ�, ���� ��ǥ ����� �ƴ�
	Matrix _matWorld = Matrix::Identity;	// ���� ��ȯ ���

	// ������ǥ�� ���� Ʈ������
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;

	// �� Ʈ�������� ���� ��ü�� ��������
	Vec3 _right;
	Vec3 _up;
	Vec3 _look;

	std::shared_ptr<Transform> m_parent;
	std::vector<shared_ptr<Transform>> m_vecChildren;
};

