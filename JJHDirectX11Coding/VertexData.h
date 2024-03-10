#pragma once

// ���ؽ� ���� ����

struct VertexTextureData
{
	Vec3 position = Vec3::Zero;
	Vec2 uv = Vec2::Zero;

	// �� ���ؽ� �����Ϳ� ���� ��ǲ ���̾ƿ��� �ƿ� static���� ��� ����
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};

struct VertexColorData
{
	Vec3 position = Vec3::Zero;
	Color color = { 0.f,0.f,0.f, 0.f };

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> descs;
};