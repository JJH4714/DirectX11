#pragma once

#include "Geometry.h"

// ������ ������ ������ִ� ���� Ŭ����
class GeometryHelper
{
public:
	// �簢��
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry);
};