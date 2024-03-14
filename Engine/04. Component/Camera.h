#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective,	// 원근 투영 - 원근법 적용 ( 3D )
	Orthographic,	// 직교 투영 - 원근법 필요없고 그냥 범위 안에 들면 다 똑같이 보임 ( UI , 2D )
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
	Matrix _matView = Matrix::Identity;	// 월드 -> 카메라 변환 행렬
	Matrix _matProjection = Matrix::Identity;	// 카메라 -> 투영 변환

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

