#include "pch.h"
#include "RasterizerState.h"

RasterizerState::RasterizerState(ComPtr<ID3D11Device> device) : m_device(device)
{
}

RasterizerState::~RasterizerState()
{
}

void RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// 채우는 방식
	// FILL_SOLID :
	// FILL_WIREFRAME : 와이어프레임(프레임쪽)만. 안은 안 채움
	desc.FillMode = D3D11_FILL_SOLID;
	//desc.FillMode = D3D11_FILL_WIREFRAME;
	// 컬링. 렌더 스킵하는 건데, 오클루전 컬링 같은 그거 맞음
	//CULL_FRONT : 앞면은 그리지 않겠다
	//CULL_BACK : 후면은 그리지 않겠다
	desc.CullMode = D3D11_CULL_BACK;
	// 앞/뒤 는 어떻게 판별할까? desc.FrontCounterClockwise

	// 앞이 반시계인가? 맞다/아니다 
	// Clockwise : 시계방향 , CounterClockwise : 반시계방향
	// false(시계방향) 기준 : 카메라가 볼 때 정점 순서가 시계방향이면, 그건 앞이다.
	// 초기에 인덱스버퍼를 시계방향으로 잡아줬던 이유가 이거...
	desc.FrontCounterClockwise = false;
	HRESULT hr = m_device->CreateRasterizerState(&desc, m_rasterizerState.GetAddressOf());
	CHECK_HR(hr);
}