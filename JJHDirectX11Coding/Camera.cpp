#include "pch.h"
#include "Camera.h"

Matrix Camera::m_matView = Matrix::Identity;
Matrix Camera::m_matProjection = Matrix::Identity;

Camera::Camera() : Component(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	// 월드->카메라 변환행렬 구하기
	// 방법 1
	/*
	// 카메라가 현재 보고 있는 위치
	Vec3 eyePosition = GetTransform()->GetPosition();
	// 카메라가 바라보는 룩벡터
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	// 카메라의 위 방향 벡터. 임의로 넘겨줘도 상관없고, 보통 Up을 사용함
	// 일단 트랜스폼 알면 그냥 그걸로 넘겨주자
	//Vec3 upDirection = Vec3::Up;
	Vec3 upDirection = GetTransform()->GetUp();

	// 카메라가 바라보는 룩벡터와 위 방향벡터를 이용해 외적을 하여 Right 벡터 구하고,
	// 구한 Right벡터와 룩벡터 외적으로 Up벡터를 구해줌
	m_matView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	*/


	// 방법 2
	// 월드좌표를 카메라좌표로 변환한다는 것은, '카메라좌표계에서 월드좌표계로 변환하는 행렬'의 역행렬과도 같다.
	m_matView = GetTransform()->GetWorldMatrix().Invert();

	// 카메라 -> 투영 변환
	// 궁금하면 봐도 좋고, 일단 변환해준다고 알아두면 됨
	if (m_type == ProjectionType::Perspective)
		// fovAngle, 비율, near, far
		m_matProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	else
		m_matProjection = ::XMMatrixOrthographicLH(8.f, 6.f, 0.f, 1.f);
}
