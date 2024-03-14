#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() 
	: Component(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height = static_cast<float>(GAME->GetGameDesc().height);
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
	/*
	// ����->ī�޶� ��ȯ��� ���ϱ�
	// ��� 1
	// ī�޶� ���� ���� �ִ� ��ġ
	Vec3 eyePosition = GetTransform()->GetPosition();
	// ī�޶� �ٶ󺸴� �躤��
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	// ī�޶��� �� ���� ����. ���Ƿ� �Ѱ��൵ �������, ���� Up�� �����
	// �ϴ� Ʈ������ �˸� �׳� �װɷ� �Ѱ�����
	//Vec3 upDirection = Vec3::Up;
	Vec3 upDirection = GetTransform()->GetUp();

	// ī�޶� �ٶ󺸴� �躤�Ϳ� �� ���⺤�͸� �̿��� ������ �Ͽ� Right ���� ���ϰ�,
	// ���� Right���Ϳ� �躤�� �������� Up���͸� ������
	//m_matView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	*/

	// ��� 2
	// ������ǥ�� ī�޶���ǥ�� ��ȯ�Ѵٴ� ����, 'ī�޶���ǥ�迡�� ������ǥ��� ��ȯ�ϴ� ���'�� ����İ��� ����.
	//_matView = GetTransform()->GetWorldMatrix().Invert();
	S_MatView = GetTransform()->GetWorldMatrix().Invert();

	// ī�޶� -> ���� ��ȯ
	S_MatProjection = ::XMMatrixPerspectiveFovLH(_fov, _width / _height, _near, _far);

	//if (m_type == ProjectionType::Perspective)
	//	// fovAngle, ����, near, far
	//	_matProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	//else
	//	_matProjection = ::XMMatrixOrthographicLH(8.f, 6.f, 0.f, 1.f);
}
