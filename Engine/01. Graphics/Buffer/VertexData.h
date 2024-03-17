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

	// 노멀벡터 : 표면의 방향을 나타내는 벡터로, 표면 정점에서 수직으로 나가는 방향
	// 정점의 노멀벡터를 이용해 빛 연산 등이 얼마나 적용될지 계산
	Vec3 normal = { 0, 0, 0 };
};