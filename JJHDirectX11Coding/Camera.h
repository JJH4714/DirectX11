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


public:
	// 월드 -> 카메라 변환 행렬
	static Matrix m_matView;
	// 카메라 -> 투영 변환
	static Matrix m_matProjection;

private:
	ProjectionType m_type = ProjectionType::Orthographic;
};

