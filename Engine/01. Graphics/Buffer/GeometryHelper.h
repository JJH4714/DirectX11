#pragma once

#include "Geometry.h"

// 기하학 정보를 만들어주는 헬퍼 클래스
class GeometryHelper
{
public:
	// 사각형
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);
	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	// 육면체
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	// 구
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	// 터레인(지형만들 때 높낮이)  인자로 그리드 크기 정해줘야 함
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureNormalData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureNormalData>> geometry, int32 sizeX, int32 sizeZ);
};