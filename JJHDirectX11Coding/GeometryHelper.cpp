#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	std::vector<VertexColorData> vecVertices;

	// 인덱스버퍼 관련 : 사각형 만들 때, 삼각형 두개 만들면 정점 6개 써야 하는데... 그것보다
	// 버텍스에 인덱스를 매겨서 정점의 수를 줄여보면 어떨까. (중복되는 정점 인덱스 매겨서)
	vecVertices.resize(4);

	// 사각형
	vecVertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vecVertices[0].color = color;

	vecVertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vecVertices[1].color = color;

	vecVertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	vecVertices[2].color = color;

	vecVertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	vecVertices[3].color = color;

	geometry->SetVertices(vecVertices);

	std::vector<uint32> vecIndices = { 0,1,2,2,1,3 };
	geometry->SetIndicies(vecIndices);
}

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexTextureData>> geometry)
{
	std::vector<VertexTextureData> vecVertices;
	vecVertices.resize(4);

	// 사각형
	vecVertices[0].position = Vec3(-0.5f, -0.5f, 0.f);
	vecVertices[0].uv = Vec2(0.0f, 1.0f);

	vecVertices[1].position = Vec3(-0.5f, 0.5f, 0.f);
	vecVertices[1].uv = Vec2(0.0f, 0.0f);

	vecVertices[2].position = Vec3(0.5f, -0.5f, 0.f);
	vecVertices[2].uv = Vec2(1.0f, 1.0f);

	vecVertices[3].position = Vec3(0.5f, 0.5f, 0.f);
	vecVertices[3].uv = Vec2(1.0f, 0.0f);

	geometry->SetVertices(vecVertices);

	std::vector<uint32> vecIndices = { 0,1,2,2,1,3 };
	geometry->SetIndicies(vecIndices);
}
