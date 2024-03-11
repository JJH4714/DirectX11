#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,	// ���� ���� - ���ٹ� ���� ( 3D )
	Orthographic,	// ���� ���� - ���ٹ� �ʿ���� �׳� ���� �ȿ� ��� �� �Ȱ��� ���� ( UI , 2D )
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type) { m_type = type; }
	const ProjectionType GetProjectionType() const { return m_type; }

	void UpdateMatrix();


public:
	// ���� -> ī�޶� ��ȯ ���
	static Matrix m_matView;
	// ī�޶� -> ���� ��ȯ
	static Matrix m_matProjection;

private:
	ProjectionType m_type = ProjectionType::Orthographic;
};

