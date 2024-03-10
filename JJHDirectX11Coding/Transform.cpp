#include "pch.h"
#include "Transform.h"

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

Vec3 ToEulerAngles(Quaternion q) {
	Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - M_PI / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void Transform::UpdateTransform()
{
	// SRT �������
	Matrix matScale = Matrix::CreateScale(m_localScale);
	Matrix matRotation = Matrix::CreateRotationX(m_localRotation.x);
	matRotation *= Matrix::CreateRotationY(m_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(m_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(m_localPosition);

	m_matLocal = matScale * matRotation * matTranslation;

	// �θ� �ִٸ�, �θ� ���� ��ǥ�� ���ٰ� �� �� ����
	if (HasParent())
	{
		// �θ� �ִٸ�, �θ� ���� ��ǥ�� ���ٰ� �� �� ����
		// '�����̰���' �� '��(�θ���� ���)' �� �ش�
		m_matWorld = m_matLocal * m_parent->GetWorldMatrix();
	}
	else
	{
		// �θ� ���ٸ�, �ΰ��� ����
		m_matWorld = m_matLocal;
	}
	
	Quaternion quat;

	m_matWorld.Decompose(m_scale, quat, m_position);
	m_rotation = ToEulerAngles(quat);


	// ���� ��ȯ ��Ŀ���
	// _11, _12, _13 : ���� ��ǥ�迡�� Right ����
	// _21, _22, _23 : ���� ��ǥ�迡�� Up ����
	// _31, _32, _33 : ���� ��ǥ�迡�� Look ����
	// �̰� ��� 2... ��� �� �ص� �Ǵϱ� ��

	// ��� 1
	//m_right = Vec3::TransformNormal(Vec3::Right, m_matWorld);
	//m_up = Vec3::TransformNormal(Vec3::Up, m_matWorld);
	//// @@ JJH : �츮�� �����ϴ� Forward�� { 0.f, 0.f, 1.f } ������, ������ Backward�� ��Ű�... Forward�� { 0.f, 0.f, -1.f } �̴� �츮�� ������ ��ǥ��� ���� �ٸ��ٴ� �� ����..
	//m_look = Vec3::TransformNormal(Vec3::Backward, m_matWorld);

	// ��� 2
	/*m_right = GetRigt();
	m_up = GetUp();
	m_look = GetLook();*/

	// �ڽĵ鵵 Ʈ������ ������Ʈ (�θ� �� �ٲ�� �� �ٲ�ϱ�)
	for (const auto& child : m_vecChildren)
		child->UpdateTransform();
}

void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		// �θ��� �����Ͽ� ���� �ڽ��� �����Ͽ��� ������ ��
		// �ϴ� ��������� �ڽ��� �������� �θ� �������� ������ ��
		// ���� �ڽ��� ���� �������� 2�̰� �θ��� ���� �������� 4�� , �ڽ��� ���� �������� 1/2(2/4)
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
		// '�� �θ��� ���� ��ȯ���' �� ����� -> ������ǥ�迡�� �θ��� ��ǥ��� ��ȯ�ϴ� ���
		Matrix worldToParentLocalMatrix = m_parent->GetWorldMatrix().Invert();

		Vec3 rotation;
		// ������ǥ�� '������ǥ��->�θ���ǥ��' ���ϸ�? �θ���ǥ�迡���� ��ǥ�� ��ȯ
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
		// '�� �θ��� ���� ��ȯ���' �� ����� -> ������ǥ�迡�� �θ��� ��ǥ��� ��ȯ�ϴ� ���
		Matrix worldToParentLocalMatrix = m_parent->GetWorldMatrix().Invert();

		Vec3 position;
		// ������ǥ�� '������ǥ��->�θ���ǥ��' ���ϸ�? �θ���ǥ�迡���� ��ǥ�� ��ȯ
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}
}
