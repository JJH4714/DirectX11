#pragma once

#include "Geometry.h"

// ������ ������ ������ִ� ���� Ŭ����
class GeometryHelper
{
public:
	// �簢��
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	// ����ü
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	// ��
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	// �ͷ���(�������� �� ������)  ���ڷ� �׸��� ũ�� ������� ��
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ);
};