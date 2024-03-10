#pragma once

// 버텍스 정보 관련

struct VertexTextureData
{
	Vec3 position = Vec3::Zero;
	Vec2 uv = Vec2::Zero;

	// 이 버텍스 데이터에 대한 인풋 레이아웃을 아예 static으로 들고 있음
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData
{
	Vec3 position = Vec3::Zero;
	Color color = { 0.f,0.f,0.f, 0.f };

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};