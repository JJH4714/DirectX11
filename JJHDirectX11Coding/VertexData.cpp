#include "pch.h"
#include "VertexData.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> VertexTextureData::descs =
{
	//{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float ���� 32��Ʈ 3����*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,12/*�� �����Ϳ��� �� ����Ʈ �ڿ� ��ġ�Ǵ���. �տ��� float 3���ϱ� 12����Ʈ*/, D3D11_INPUT_PER_VERTEX_DATA, 0}

	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float ���� 32��Ʈ 3����*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT/*�˾Ƽ� ���*/, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> VertexColorData::descs =
{
	//{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float ���� 32��Ʈ 3����*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,12/*�� �����Ϳ��� �� ����Ʈ �ڿ� ��ġ�Ǵ���. �տ��� float 3���ϱ� 12����Ʈ*/, D3D11_INPUT_PER_VERTEX_DATA, 0}

	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float ���� 32��Ʈ 3����*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0 , DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT/*�˾Ƽ� ���*/, D3D11_INPUT_PER_VERTEX_DATA, 0}
};