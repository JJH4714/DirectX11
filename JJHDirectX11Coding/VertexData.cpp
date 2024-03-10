#include "pch.h"
#include "VertexData.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> VertexTextureData::descs =
{
	//{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float 각각 32비트 3개다*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,12/*앞 데이터에서 몇 바이트 뒤에 배치되는지. 앞에서 float 3개니까 12바이트*/, D3D11_INPUT_PER_VERTEX_DATA, 0}

	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float 각각 32비트 3개다*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,D3D11_APPEND_ALIGNED_ELEMENT/*알아서 계산*/, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const std::vector<D3D11_INPUT_ELEMENT_DESC> VertexColorData::descs =
{
	//{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float 각각 32비트 3개다*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	//{"TEXCOORD", 0 , DXGI_FORMAT_R32G32_FLOAT, 0,12/*앞 데이터에서 몇 바이트 뒤에 배치되는지. 앞에서 float 3개니까 12바이트*/, D3D11_INPUT_PER_VERTEX_DATA, 0}

	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT /*float 각각 32비트 3개다*/, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"COLOR", 0 , DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT/*알아서 계산*/, D3D11_INPUT_PER_VERTEX_DATA, 0}
};