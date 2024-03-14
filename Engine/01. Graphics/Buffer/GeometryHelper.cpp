#include "pch.h"
#include "GeometryHelper.h"

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color)
{
	vector<VertexColorData> vtx;
	vtx.resize(4);

	vtx[0].position = Vec3(-0.5f, 0.5f, 0.0f);
	vtx[0].color = color;

	vtx[1].position = Vec3(0.5f, 0.5f, 0.0f);
	vtx[1].color = color;

	vtx[2].position = Vec3(0.5f, -0.5f, 0.0f);
	vtx[2].color = color;

	vtx[3].position = Vec3(-0.5f, -0.5f, 0.0f);
	vtx[3].color = color;
	geometry->SetVertices(vtx);

	// 0 1
	// 3 2
	
	// 레스터라이저 따로 선택 안 하면 인덱스 순서는 시계방향으로...
	vector<uint32> indices = { 0,1,2, 2,3,0 };
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	vector<VertexTextureData> vtx;
	vtx.resize(4);

	vtx[0].position = Vec3(-0.5f, 0.5f, 0.0f);
	vtx[0].uv = Vec2(0.f, 0.f);

	vtx[1].position = Vec3(0.5f, 0.5f, 0.0f);
	vtx[1].uv = Vec2(1.f, 0.f);

	vtx[2].position = Vec3(0.5f, -0.5f, 0.0f);
	vtx[2].uv = Vec2(1.f, 1.f);

	vtx[3].position = Vec3(-0.5f, -0.5f, 0.0f);
	vtx[3].uv = Vec2(0.f, 1.f);
	geometry->SetVertices(vtx);

	vector<uint32> indices = { 0,1,2, 2,3,0 };
	geometry->SetIndices(indices);
}

void GeometryHelper::CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry)
{
	// 일반 사각형은 인덱스버퍼 사용 시 정점 4개만 있으면 됨.
	// 그래서 큐브도 정점 8개 있으면 된다 생각들겠지만...그렇진 않음
	// 사각형 육면체라서 정점24개..
	
	float w2 = 0.5f;	// width
	float h2 = 0.5f;	// height
	float d2 = 0.5f;	// depth

	vector<VertexTextureData> vtx(24);

	// 앞면
	vtx[0] = VertexTextureData(Vec3(-w2, -h2, -d2), Vec2(0.f, 1.f));
	vtx[1] = VertexTextureData(Vec3(-w2, +h2, -d2), Vec2(0.f, 0.f));
	vtx[2] = VertexTextureData(Vec3(+w2, +h2, -d2), Vec2(1.f, 0.f));
	vtx[3] = VertexTextureData(Vec3(+w2, -h2, -d2), Vec2(1.f, 1.f));
	// 뒷면
	vtx[4] = VertexTextureData(Vec3(-w2, -h2, +d2), Vec2(1.f, 1.f));
	vtx[5] = VertexTextureData(Vec3(+w2, -h2, +d2), Vec2(0.f, 1.f));
	vtx[6] = VertexTextureData(Vec3(+w2, +h2, +d2), Vec2(0.f, 0.f));
	vtx[7] = VertexTextureData(Vec3(-w2, +h2, +d2), Vec2(1.f, 0.f));
	// 윗면
	vtx[8] = VertexTextureData(Vec3(-w2, +h2, -d2), Vec2(0.f, 1.f));
	vtx[9] = VertexTextureData(Vec3(-w2, +h2, +d2), Vec2(0.f, 0.f));
	vtx[10] = VertexTextureData(Vec3(+w2, +h2, +d2), Vec2(1.f, 0.f));
	vtx[11] = VertexTextureData(Vec3(+w2, +h2, -d2), Vec2(1.f, 1.f));
	// 아랫면
	vtx[12] = VertexTextureData(Vec3(-w2, -h2, -d2), Vec2(1.f, 1.f));
	vtx[13] = VertexTextureData(Vec3(+w2, -h2, -d2), Vec2(0.f, 1.f));
	vtx[14] = VertexTextureData(Vec3(+w2, -h2, +d2), Vec2(0.f, 0.f));
	vtx[15] = VertexTextureData(Vec3(-w2, -h2, +d2), Vec2(1.f, 0.f));
	// 왼쪽면
	vtx[16] = VertexTextureData(Vec3(-w2, -h2, +d2), Vec2(0.f, 1.f));
	vtx[17] = VertexTextureData(Vec3(-w2, +h2, +d2), Vec2(0.f, 0.f));
	vtx[18] = VertexTextureData(Vec3(-w2, +h2, -d2), Vec2(1.f, 0.f));
	vtx[19] = VertexTextureData(Vec3(-w2, -h2, -d2), Vec2(1.f, 1.f));
	// 오른쪽면
	vtx[20] = VertexTextureData(Vec3(+w2, -h2, -d2), Vec2(0.f, 1.f));
	vtx[21] = VertexTextureData(Vec3(+w2, +h2, -d2), Vec2(0.f, 0.f));
	vtx[22] = VertexTextureData(Vec3(+w2, +h2, +d2), Vec2(1.f, 0.f));
	vtx[23] = VertexTextureData(Vec3(+w2, -h2, +d2), Vec2(1.f, 1.f));

	geometry->SetVertices(vtx);

	vector<uint32> idx(36);

	// 앞면
	idx[0] = 0;	idx[1] = 1;	idx[2] = 2;
	idx[3] = 0;	idx[4] = 2;	idx[5] = 3;
	// 뒷면
	idx[6] = 4;	idx[7] = 5;	idx[8] = 6;
	idx[9] = 4;	idx[10] = 6; idx[11] = 7;
	// 윗면
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// 아랫면
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// 왼쪽면
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// 오른쪽면
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	geometry->SetIndices(idx);
}

void GeometryHelper::CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry)
{

}

void GeometryHelper::CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry)
{

}
