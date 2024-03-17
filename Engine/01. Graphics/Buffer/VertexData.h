#pragma once

struct VertexData
{
	Vec3 position = { 0, 0, 0 };
};

struct VertexTextureData
{
	Vec3 position = { 0, 0, 0 };
	Vec2 uv = { 0, 0 };
};

struct VertexColorData
{
	Vec3 position = { 0, 0, 0 };
	Color color = { 0, 0, 0, 0 };
};

struct VertexTextureNormalData
{
	Vec3 position = { 0, 0, 0 };
	Vec2 uv = { 0, 0 };

	// ��ֺ��� : ǥ���� ������ ��Ÿ���� ���ͷ�, ǥ�� �������� �������� ������ ����
	// ������ ��ֺ��͸� �̿��� �� ���� ���� �󸶳� ������� ���
	Vec3 normal = { 0, 0, 0 };
};