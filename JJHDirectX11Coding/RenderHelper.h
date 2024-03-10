#pragma once

struct CameraData
{
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct TransformData
{
	Matrix matWorld = Matrix::Identity;
};


// CameraData, TransformData�� 16����Ʈ�� ������ �־ ����������
// GPU ������ �ѱ� �� 16���� ������� ��
struct AnimationData
{
	Vec2 spriteOffset;
	Vec2 spriteSize;
	Vec2 textureSize;

	float useAnimation;	// �ִϸ��̼� �������. ���̴��� �Ѱ��� �� boolean �� ����;
	float fadding;	// 16 ���� ����..
};