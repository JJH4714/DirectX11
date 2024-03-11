#include "pch.h"
#include "InputLayout.h"

InputLayout::InputLayout(ComPtr<ID3D11Device> device) : m_device(device)
{
}

InputLayout::~InputLayout()
{
}

void InputLayout::Create(const std::vector<D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob)
{
	const int32 count = static_cast<int32>(descs.size());
	HRESULT hr = m_device->CreateInputLayout(
		descs.data(),
		count/*InputLayout에 들어가는 데이터 수*/,
		blob->GetBufferPointer(),	// 버텍스 셰이더의 블롭 정보
		blob->GetBufferSize(),		// 버텍스 셰이더의 블롭 사이즈
		m_inputLayout.GetAddressOf()	// ID3D11InputLayout 에 담아줌
	);
	ASSERT(hr);
}
