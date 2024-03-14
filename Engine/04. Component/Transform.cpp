#include "pch.h"

Transform::Transform() : Component(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{
}

void Transform::Update()
{
}

Vec3 ToEulerAngles(Quaternion q) 
{
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = static_cast<float>(std::atan2(sinr_cosp, cosr_cosp));

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = static_cast<float>(2 * std::atan2(sinp, cosp) - XM_PI / 2);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = static_cast<float>(std::atan2(siny_cosp, cosy_cosp));

	return angles;
}

void Transform::UpdateTransform()
{
	// SRT 순서대로
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRotation * matTranslation;

	// 부모가 있다면, 부모가 월드 좌표계 쓴다고 할 순 없다
	if (HasParent())
	{
		// 부모가 있다면, 부모가 월드 좌표계 쓴다고 할 순 없다
		// '스자이공부' 의 '부(부모님의 행렬)' 에 해당
		_matWorld = _matLocal * m_parent->GetWorldMatrix();
	}
	else
	{
		// 부모가 없다면, 두개가 같음
		_matWorld = _matLocal;
	}
	
	Quaternion quat;

	_matWorld.Decompose(_scale, quat, _position);
	_rotation = ToEulerAngles(quat);


	// 월드 변환 행렬에서
	// _11, _12, _13 : 로컬 좌표계에서 Right 벡터
	// _21, _22, _23 : 로컬 좌표계에서 Up 벡터
	// _31, _32, _33 : 로컬 좌표계에서 Look 벡터
	// 이게 방식 2... 계산 안 해도 되니까 ㅋ

	// 방식 1
	//m_right = Vec3::TransformNormal(Vec3::Right, m_matWorld);
	//m_up = Vec3::TransformNormal(Vec3::Up, m_matWorld);
	////우리가 생각하는 Forward는 { 0.f, 0.f, 1.f } 이지만, 실제론 Backward가 요거고... Forward는 { 0.f, 0.f, -1.f } 이니 우리가 생각한 좌표계와 조금 다르다는 거 참고..
	//m_look = Vec3::TransformNormal(Vec3::Backward, m_matWorld);

	// 방식 2
	/*m_right = GetRigt();
	m_up = GetUp();
	m_look = GetLook();*/

	// 자식들도 트랜스폼 업데이트 (부모 쪽 바뀌면 다 바뀌니까)
	for (const auto& child : m_vecChildren)
		child->UpdateTransform();
}

void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		// 부모의 스케일에 따라 자식의 스케일에도 영향이 감
		// 일단 결과적으론 자식의 스케일은 부모 스케일을 나눠야 함
		// 예로 자식이 월드 스케일이 2이고 부모의 월드 스케일이 4면 , 자식의 로컬 스케일은 1/2(2/4)
		Vec3 parentScale = m_parent->GetScale();
		Vec3 scale = worldScale;
		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const Vec3& worldRotation)
{
	if (HasParent())
	{
		// '내 부모의 월드 변환행렬' 의 역행렬 -> 월드좌표계에서 부모의 좌표계로 변환하는 행렬
		Matrix worldToParentLocalMatrix = m_parent->GetWorldMatrix().Invert();

		Vec3 rotation;
		// 월드좌표에 '월드좌표계->부모좌표계' 곱하면? 부모좌표계에서의 좌표로 변환
		rotation.Transform(worldRotation, worldToParentLocalMatrix);

		SetLocalPosition(rotation);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent())
	{
		// 월드좌표를 부모좌표계의 좌표로 변환할 필요가 있음
		// '내 부모의 월드 변환행렬' 의 역행렬 -> 월드좌표계에서 부모의 좌표계로 변환하는 행렬
		Matrix worldToParentLocalMatrix = m_parent->GetWorldMatrix().Invert();

		Vec3 position;
		// 월드좌표에 '월드좌표계->부모좌표계' 곱하면? 부모좌표계에서의 좌표로 변환
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		// 부모가 없다 -> 로컬좌표계가 곧 월드좌표계이니 바로 넣음 
		SetLocalPosition(worldPosition);
	}
}
