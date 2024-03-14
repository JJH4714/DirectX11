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

	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFov(float value) { _fov = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }

	const Matrix& GetViewMatrix() const { return _matView; }
	const Matrix& GetProjection() const { return _matProjection; }

private:
	Matrix _matView = Matrix::Identity;	// ���� -> ī�޶� ��ȯ ���
	Matrix _matProjection = Matrix::Identity;	// ī�޶� -> ���� ��ȯ

	ProjectionType m_type = ProjectionType::Perspective;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

