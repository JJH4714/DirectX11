#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateRectangle(std::shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	std::vector<VertexColorData> vecVertices;

	// �ε������� ���� : �簢�� ���� ��, �ﰢ�� �ΰ� ����� ���� 6�� ��� �ϴµ�... �װͺ���
	// ���ؽ��� �ε����� �Űܼ� ������ ���� �ٿ����� ���. (�ߺ��Ǵ� ���� �ε��� �Űܼ�)
	vecVertices.resize(4);

	// �簢��
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

	// �簢��
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
